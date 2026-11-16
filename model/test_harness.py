#!/usr/bin/env python3
import json
import os
import re
import subprocess
import sys
import time
import urllib.request

MODEL_DIR = os.path.dirname(os.path.abspath(__file__))
QUESTIONS_FILE = os.path.join(MODEL_DIR, "test_questions.json")
REPORT_FILE = os.path.join(MODEL_DIR, "BENCHMARK_RESULTS.md")
OLLAMA_API = "http://127.0.0.1:11434/api/generate"

def query_ollama(model_name: str, prompt: str, system: str = ""):
    payload = {
        "model": model_name,
        "prompt": prompt,
        "system": system,
        "stream": False,
        "options": {
            "temperature": 0.2,
            "top_p": 0.95,
        }
    }
    data = json.dumps(payload).encode("utf-8")
    req = urllib.request.Request(
        OLLAMA_API,
        data=data,
        headers={"Content-Type": "application/json"}
    )
    start_time = time.time()
    with urllib.request.urlopen(req) as resp:
        res = json.loads(resp.read().decode("utf-8"))
    wall_duration = time.time() - start_time
    return res, wall_duration

def clean_code(raw_text: str) -> str:
    # Extract code from ```c ... ``` if present
    match = re.search(r"```(?:c|cpp)?\s*([\s\S]*?)\s*```", raw_text)
    if match:
        return match.group(1).strip()
    return raw_text.strip()

def run_tests(model_name: str = "qwen2.5-coder:7b"):
    with open(QUESTIONS_FILE, "r") as f:
        data = json.load(f)
    
    tests = data.get("tests", [])
    results = []

    print(f"\n=======================================================")
    print(f"  Starting DSA Benchmark for Model: {model_name}")
    print(f"  Total Test Cases: {len(tests)}")
    print(f"=======================================================\n")

    system_prompt = (
        "You are an expert C programmer specializing in Data Structures and Algorithms. "
        "Complete only the requested function body or definition in clean, efficient, bug-free C. "
        "Do not include main(), do not redefine helper functions or structs that are already provided. "
        "Only return the C code."
    )

    for idx, test in enumerate(tests, 1):
        test_id = test["id"]
        title = test["title"]
        prompt = test["prompt"]
        prefix = test["prefix"]
        suffix = test["suffix"]
        signature = test.get("signature", "")

        print(f"[{idx}/{len(tests)}] Testing: {title} ({signature}) ...")
        
        full_prompt = (
            f"Here is the context and definitions:\n```c\n{prefix}\n```\n\n"
            f"Task: {prompt}\n\n"
            f"Provide the exact implementation in C:"
        )

        try:
            resp, wall_time = query_ollama(model_name, full_prompt, system_prompt)
            raw_response = resp.get("response", "")
            eval_count = resp.get("eval_count", 0)
            eval_duration_ns = resp.get("eval_duration", 1)
            tps = eval_count / (eval_duration_ns / 1e9) if eval_duration_ns > 0 else 0
            
            code = clean_code(raw_response)
        except Exception as e:
            print(f"  [!] Ollama query failed: {e}")
            results.append({
                "test": test,
                "status": "API_ERROR",
                "error": str(e),
                "code": "",
                "wall_time": 0,
                "tps": 0
            })
            continue

        # Stitch full C file
        full_code = f"{prefix}\n// --- Generated Implementation ---\n{code}\n// --- Test Verification ---\n{suffix}\n"
        src_path = os.path.join(MODEL_DIR, f"{test_id}_test.c")
        bin_path = os.path.join(MODEL_DIR, f"{test_id}_test")

        with open(src_path, "w") as f:
            f.write(full_code)

        # Compile with gcc
        compile_cmd = ["gcc", "-Wall", "-Wextra", src_path, "-o", bin_path]
        comp = subprocess.run(compile_cmd, capture_output=True, text=True)

        if comp.returncode != 0:
            print(f"  ❌ Compilation Failed!")
            results.append({
                "test": test,
                "status": "COMPILE_FAIL",
                "code": code,
                "compile_error": comp.stderr,
                "wall_time": wall_time,
                "eval_count": eval_count,
                "tps": tps
            })
            continue

        # Run test binary
        run = subprocess.run([bin_path], capture_output=True, text=True, timeout=5)
        if run.returncode == 0:
            print(f"  ✅ PASS! (Speed: {tps:.2f} tok/s, Latency: {wall_time:.2f}s)")
            results.append({
                "test": test,
                "status": "PASS",
                "code": code,
                "stdout": run.stdout.strip(),
                "wall_time": wall_time,
                "eval_count": eval_count,
                "tps": tps
            })
        else:
            print(f"  ❌ Runtime Assertion / Crash: exit code {run.returncode}")
            results.append({
                "test": test,
                "status": "RUNTIME_FAIL",
                "code": code,
                "stderr": run.stderr.strip(),
                "wall_time": wall_time,
                "eval_count": eval_count,
                "tps": tps
            })

    # Generate Markdown Report
    passed = sum(1 for r in results if r["status"] == "PASS")
    total = len(results)
    avg_tps = sum(r.get("tps", 0) for r in results) / total if total > 0 else 0

    with open(REPORT_FILE, "w") as f:
        f.write(f"# DSA Benchmark Report: {model_name}\n\n")
        f.write(f"- **Date**: {time.strftime('%Y-%m-%d %H:%M:%S')}\n")
        f.write(f"- **System**: AMD Ryzen 7 7735HS (8C/16T) + Radeon 680M\n")
        f.write(f"- **Overall Score**: **{passed}/{total} ({passed/total*100:.1f}%) Passed**\n")
        f.write(f"- **Average Generation Speed**: **{avg_tps:.2f} tokens/sec**\n\n")

        f.write("## Summary Table\n\n")
        f.write("| ID | Problem | Status | Speed (tok/s) | Latency (s) |\n")
        f.write("| :--- | :--- | :--- | :--- | :--- |\n")
        for r in results:
            tid = r["test"]["id"]
            title = r["test"]["title"]
            st = r["status"]
            icon = "✅ PASS" if st == "PASS" else "❌ " + st
            f.write(f"| `{tid}` | {title} | {icon} | {r.get('tps', 0):.2f} | {r.get('wall_time', 0):.2f}s |\n")

        f.write("\n## Detailed Test Outputs\n\n")
        for r in results:
            t = r["test"]
            f.write(f"### {t['title']} (`{t['id']}`)\n\n")
            f.write(f"**Status**: `{r['status']}`\n\n")
            f.write("```c\n" + r.get("code", "") + "\n```\n\n")
            if "compile_error" in r:
                f.write("**Compiler Diagnostics**:\n```text\n" + r["compile_error"] + "\n```\n\n")
            if "stderr" in r and r["stderr"]:
                f.write("**Runtime Error**:\n```text\n" + r["stderr"] + "\n```\n\n")

    print(f"\n=======================================================")
    print(f"  Benchmark Complete! Passed: {passed}/{total}")
    print(f"  Report saved to: {REPORT_FILE}")
    print(f"=======================================================\n")

if __name__ == "__main__":
    model = sys.argv[1] if len(sys.argv) > 1 else "qwen2.5-coder:7b"
    run_tests(model)

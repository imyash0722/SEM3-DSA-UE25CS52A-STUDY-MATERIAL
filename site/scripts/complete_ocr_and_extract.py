#!/usr/bin/env python3
"""
Comprehensive pipeline to:
1. Ensure all documents are converted to PDFs (Units 1, 2, 3 Notes & Slides)
2. Build combined PDFs for Unit 3 (Combined Notes & Combined Slides)
3. OCR all PDFs (using ocrmypdf --skip-text --output-type pdf)
4. Extract all text from all OCR'd PDFs (individual .txt files and combined unit text files)
"""

import os
import sys
import glob
import re
import subprocess
import shutil
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor, as_completed
import fitz  # PyMuPDF

WORKSPACE_ROOT = Path("/mnt/shared/sem3/DSA").resolve()

def natural_key(string_):
    return [int(s) if s.isdigit() else s.lower() for s in re.split(r'(\d+)', str(string_))]

def run_cmd(cmd, check=True):
    p = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if check and p.returncode != 0:
        print(f"Command failed: {' '.join(str(c) for c in cmd)}\nError: {p.stderr}")
    return p

def ocr_pdf_file(pdf_path: Path):
    """
    Run ocrmypdf in-place with --skip-text --output-type pdf.
    """
    temp_pdf = pdf_path.with_name(f".tmp_{pdf_path.name}")
    cmd = [
        "uvx", "ocrmypdf",
        "--skip-text",
        "--output-type", "pdf",
        str(pdf_path),
        str(temp_pdf)
    ]
    res = run_cmd(cmd, check=False)
    if res.returncode == 0 and temp_pdf.exists() and temp_pdf.stat().st_size > 0:
        shutil.move(str(temp_pdf), str(pdf_path))
        print(f"[OCR OK] {pdf_path.name}")
        return (pdf_path, True, "OK")
    else:
        if temp_pdf.exists():
            temp_pdf.unlink()
        err_msg = res.stderr[:100].replace('\n', ' ')
        print(f"[OCR SKIP/FAIL] {pdf_path.name}: {err_msg}")
        return (pdf_path, False, err_msg)

def extract_text_from_pdf(pdf_path: Path, out_txt_path: Path):
    """
    Extract formatted text from PDF, including OCR layer and diagram image text if any.
    """
    try:
        doc = fitz.open(pdf_path)
    except Exception as e:
        print(f"[EXTRACT ERROR] Could not open {pdf_path}: {e}")
        return ""

    page_texts = []
    
    for page_num, page in enumerate(doc, 1):
        # Extract layout-preserving text
        text = page.get_text("text").strip()
        
        # Check for diagram images that might have OCRable text
        imgs = page.get_images(full=True)
        img_ocr_texts = []
        for img_info in imgs:
            xref = img_info[0]
            try:
                base_img = doc.extract_image(xref)
                w, h = base_img["width"], base_img["height"]
                # Filter out tiny icons, lines, logos
                if w < 120 or h < 60:
                    continue
                if (w, h) in [(232, 119), (293, 150)]:  # Standard header/footer logos
                    continue
                
                # Run tesseract on image
                img_bytes = base_img["image"]
                tess = subprocess.run(
                    ["tesseract", "stdin", "stdout", "--psm", "6"],
                    input=img_bytes,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.PIPE
                )
                t_out = tess.stdout.decode("utf-8", errors="replace").strip()
                if len(t_out) > 15:
                    sample = t_out[:40]
                    if sample not in text:
                        img_ocr_texts.append(t_out)
            except Exception:
                pass
        
        page_header = f"===== Page {page_num} ====="
        sections = [page_header]
        if text:
            sections.append(text)
        if img_ocr_texts:
            sections.append("[Embedded Image / Diagram OCR Text]:\n" + "\n---\n".join(img_ocr_texts))
        
        page_texts.append("\n\n".join(sections))
        
    full_text = "\n\n" + ("\n\n" + "-"*40 + "\n\n").join(page_texts) + "\n"
    out_txt_path.parent.mkdir(parents=True, exist_ok=True)
    out_txt_path.write_text(full_text, encoding="utf-8")
    print(f"[EXTRACTED] {pdf_path.name} -> {out_txt_path.name} ({len(doc)} pages, {len(full_text):,} chars)")
    return full_text

def main():
    combined_notes_dir = WORKSPACE_ROOT / "resources" / "Combined Notes"
    combined_slides_dir = WORKSPACE_ROOT / "resources" / "Combined Slides"
    extracted_text_dir = WORKSPACE_ROOT / "resources" / "extracted_text"
    extracted_text_dir.mkdir(parents=True, exist_ok=True)

    # 1. Combined and root PDFs
    combined_and_root_pdfs = [
        combined_notes_dir / "DSA Unit 1 Combined Notes.pdf",
        combined_notes_dir / "DSA Unit 2 Combined Notes.pdf",
        combined_notes_dir / "DSA Unit 3 Combined Notes.pdf",
        combined_slides_dir / "DSA Unit 1 Combined Slides.pdf",
        combined_slides_dir / "DSA Unit 2 Combined Slides.pdf",
        combined_slides_dir / "DSA Unit 3 Combined Slides.pdf",
        WORKSPACE_ROOT / "resources" / "DSA_Unit_1_MCQs_Questions_Only_Answers_at_End.pdf",
        WORKSPACE_ROOT / "resources" / "DSA_Unit_2_MCQs_Questions_Only_Answers_at_End.pdf",
        WORKSPACE_ROOT / "resources" / "Unit 1.pdf",
    ]

    # 2. Individual folders
    pdf_dirs = [
        WORKSPACE_ROOT / "resources" / "Data_Structures_and_its_Applications" / "1" / "Notes",
        WORKSPACE_ROOT / "resources" / "Data_Structures_and_its_Applications" / "1" / "Slides",
        WORKSPACE_ROOT / "resources" / "Data_Structures_and_its_Applications" / "2" / "Notes",
        WORKSPACE_ROOT / "resources" / "Data_Structures_and_its_Applications" / "2" / "Slides",
        WORKSPACE_ROOT / "resources" / "Data_Structures_and_its_Applications" / "3" / "Notes",
        WORKSPACE_ROOT / "resources" / "Data_Structures_and_its_Applications" / "3" / "Slides",
        WORKSPACE_ROOT / "resources" / "u3" / "Data_Structures_and_its_Applications" / "3" / "Notes",
        WORKSPACE_ROOT / "resources" / "u3" / "Data_Structures_and_its_Applications" / "3" / "Slides",
    ]

    all_individual_pdfs = []
    for d in pdf_dirs:
        if d.exists():
            pdfs = sorted(d.glob("*.pdf"), key=natural_key)
            all_individual_pdfs.extend(pdfs)

    all_pdfs_to_ocr = [p for p in combined_and_root_pdfs if p.exists()] + all_individual_pdfs

    print(f"Total PDFs queued for OCR: {len(all_pdfs_to_ocr)}")

    print("\n=== Running Parallel OCR on all PDFs ===")
    with ThreadPoolExecutor(max_workers=4) as executor:
        futures = {executor.submit(ocr_pdf_file, pdf): pdf for pdf in all_pdfs_to_ocr}
        for future in as_completed(futures):
            pdf = futures[future]
            try:
                future.result()
            except Exception as e:
                print(f"[OCR EXCEPTION] {pdf.name}: {e}")

    print("\n=== Extracting Text from All Individual PDFs ===")
    for pdf in all_individual_pdfs:
        txt_path = pdf.with_suffix(".txt")
        extract_text_from_pdf(pdf, txt_path)

    print("\n=== Extracting Text from Combined & Root PDFs ===")
    extract_text_from_pdf(
        combined_notes_dir / "DSA Unit 1 Combined Notes.pdf",
        extracted_text_dir / "unit1_notes.txt"
    )
    extract_text_from_pdf(
        combined_slides_dir / "DSA Unit 1 Combined Slides.pdf",
        extracted_text_dir / "unit1_slides.txt"
    )
    extract_text_from_pdf(
        WORKSPACE_ROOT / "resources" / "DSA_Unit_1_MCQs_Questions_Only_Answers_at_End.pdf",
        extracted_text_dir / "unit1_mcqs.txt"
    )
    extract_text_from_pdf(
        combined_notes_dir / "DSA Unit 2 Combined Notes.pdf",
        extracted_text_dir / "unit2_notes.txt"
    )
    extract_text_from_pdf(
        combined_slides_dir / "DSA Unit 2 Combined Slides.pdf",
        extracted_text_dir / "unit2_slides.txt"
    )
    extract_text_from_pdf(
        WORKSPACE_ROOT / "resources" / "DSA_Unit_2_MCQs_Questions_Only_Answers_at_End.pdf",
        extracted_text_dir / "unit2_mcqs.txt"
    )
    extract_text_from_pdf(
        combined_notes_dir / "DSA Unit 3 Combined Notes.pdf",
        extracted_text_dir / "unit3_notes.txt"
    )
    extract_text_from_pdf(
        combined_slides_dir / "DSA Unit 3 Combined Slides.pdf",
        extracted_text_dir / "unit3_slides.txt"
    )
    extract_text_from_pdf(
        WORKSPACE_ROOT / "resources" / "Unit 1.pdf",
        extracted_text_dir / "unit1_complete.txt"
    )

    print("\n=== Pipeline Execution Finished ===")

if __name__ == "__main__":
    main()

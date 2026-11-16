#!/usr/bin/env python3
"""
Cross-Platform Offline Server & Launcher for DSA Study Guide
Supports: Windows, Linux, macOS
- Auto-detects OS
- Checks/installs dependencies (in a clean virtualenv if needed)
- Builds static site if site/ directory is missing
- Finds an available port
- Launches local HTTP server
- Automatically opens the default browser
"""

import os
import sys
import platform
import subprocess
import socket
import threading
import time
import webbrowser
from http.server import HTTPServer, SimpleHTTPRequestHandler

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
SITE_DIR = os.path.join(BASE_DIR, "site")
CONFIG_FILE = os.path.join(BASE_DIR, "zensical.yml")
REQ_FILE = os.path.join(BASE_DIR, "requirements.txt")
VENV_DIR = os.path.join(BASE_DIR, ".venv")

def get_os_name():
    system = platform.system().lower()
    if "windows" in system:
        return "windows"
    elif "darwin" in system:
        return "macos"
    return "linux"

def find_free_port(start_port=8000, max_attempts=50):
    for port in range(start_port, start_port + max_attempts):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            if s.connect_ex(("127.0.0.1", port)) != 0:
                return port
    return start_port

def get_venv_executables():
    os_name = get_os_name()
    if os_name == "windows":
        py_bin = os.path.join(VENV_DIR, "Scripts", "python.exe")
        pip_bin = os.path.join(VENV_DIR, "Scripts", "pip.exe")
        zensical_bin = os.path.join(VENV_DIR, "Scripts", "zensical.exe")
    else:
        py_bin = os.path.join(VENV_DIR, "bin", "python")
        pip_bin = os.path.join(VENV_DIR, "bin", "pip")
        zensical_bin = os.path.join(VENV_DIR, "bin", "zensical")
    return py_bin, pip_bin, zensical_bin

def ensure_dependencies():
    """Ensure zensical or site/ is ready; install into .venv if missing."""
    if os.path.exists(os.path.join(SITE_DIR, "index.html")):
        # Pre-built site is already present
        return True

    print("🔍 Pre-built site not found. Checking Zensical build tool...")
    
    # Check if zensical is already globally in PATH
    try:
        subprocess.run(["zensical", "--version"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
        print("✅ Found system 'zensical'. Building site...")
        subprocess.run(["zensical", "build", "--config-file", CONFIG_FILE], cwd=BASE_DIR, check=True)
        return True
    except (subprocess.SubprocessError, FileNotFoundError):
        pass

    # Create virtual environment if missing
    py_bin, pip_bin, zensical_bin = get_venv_executables()
    if not os.path.exists(py_bin):
        print(f"📦 Creating local virtualenv in {VENV_DIR}...")
        subprocess.run([sys.executable, "-m", "venv", VENV_DIR], check=True)

    print("📥 Installing dependencies from requirements.txt...")
    subprocess.run([pip_bin, "install", "--upgrade", "pip"], check=True)
    subprocess.run([pip_bin, "install", "-r", REQ_FILE], check=True)

    print("🔨 Building static documentation site...")
    subprocess.run([zensical_bin, "build", "--config-file", CONFIG_FILE], cwd=BASE_DIR, check=True)
    return True

def open_browser(url, delay=1.2):
    def _open():
        time.sleep(delay)
        print(f"🚀 Opening browser at {url} ...")
        webbrowser.open(url)
    t = threading.Thread(target=_open, daemon=True)
    t.start()

class DualDirectoryHandler(SimpleHTTPRequestHandler):
    """Serve files out of the site/ directory."""
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=SITE_DIR, **kwargs)

def start_server(port):
    server_address = ("127.0.0.1", port)
    httpd = HTTPServer(server_address, DualDirectoryHandler)
    url = f"http://127.0.0.1:{port}/"
    
    os_name = get_os_name().capitalize()
    print("\n" + "=" * 65)
    print(f"  📚 DSA Offline Study Guide Server Active")
    print(f"  Platform Detected : {os_name}")
    print(f"  Serving Directory : {SITE_DIR}")
    print(f"  Local Access URL  : {url}")
    print("=" * 65)
    print("  Press [Ctrl + C] anytime to stop the server.\n")

    open_browser(url)

    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print("\n🛑 Shutting down server gracefully...")
        httpd.server_close()
        print("✅ Server stopped.")

def main():
    os_name = get_os_name()
    print(f"🖥️ Detected OS: {os_name.capitalize()}")
    
    # Ensure dependencies and built site
    ensure_dependencies()
    
    if not os.path.exists(os.path.join(SITE_DIR, "index.html")):
        print(f"❌ Error: {SITE_DIR}/index.html could not be generated.")
        sys.exit(1)

    port = find_free_port(8000)
    start_server(port)

if __name__ == "__main__":
    main()

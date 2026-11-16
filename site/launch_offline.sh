#!/usr/bin/env bash
# ==============================================================================
# Linux / macOS One-Click Offline Launcher for DSA Study Guide
# ==============================================================================
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${SCRIPT_DIR}"

# Find python3 or python
if command -v python3 &> /dev/null; then
    PY_CMD="python3"
elif command -v python &> /dev/null; then
    PY_CMD="python"
else
    echo "❌ Error: Python 3 is not installed or not in your PATH."
    exit 1
fi

"${PY_CMD}" "${SCRIPT_DIR}/launch_offline.py" "$@"

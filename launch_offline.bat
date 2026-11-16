@echo off
REM ============================================================================
REM Windows One-Click Offline Launcher for DSA Study Guide
REM ============================================================================

cd /d "%~dp0"

where python >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    python "%~dp0launch_offline.py" %*
    goto end
)

where py >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    py -3 "%~dp0launch_offline.py" %*
    goto end
)

echo [ERROR] Python 3 was not found in your PATH.
echo Please install Python 3 from https://www.python.org/ or the Microsoft Store.
pause

:end

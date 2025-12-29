@echo off
setlocal

REM ====== EDIT THESE TWO ======
set "VENV_DIR=C:\Users\xxx\python_workspace\embedded_system\env-embedded"
set "SCRIPT_PATH=C:\Users\xxx\STM32\Workspace\Project\STM32_HW_operational\python_project\monitor_uart_gui.py"
REM ============================

REM UART settings : only needed when monitor_uart script is lauched
set "PORT=COM3"
set "BAUD=115200"
REM set "LOG=C:\path\to\uart_log.txt"

set "PYEXE=%VENV_DIR%\Scripts\python.exe"

if not exist "%PYEXE%" (
  echo ERROR: Cannot find venv python: "%PYEXE%"
  pause
  exit /b 1
)

if not exist "%SCRIPT_PATH%" (
  echo ERROR: Cannot find script: "%SCRIPT_PATH%"
  pause
  exit /b 1
)

REM Run using venv python (no activation needed)
"%PYEXE%" "%SCRIPT_PATH%" REM --port "%PORT%" --baud "%BAUD%"
REM "%PYEXE%" "%SCRIPT_PATH%" --port "%PORT%" --baud "%BAUD%" --log "%LOG%"

pause
endlocal

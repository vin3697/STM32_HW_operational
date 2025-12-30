
# STM32 UART Monitor (Python Tkinter GUI)
![alt text](images/uart_demo_light.gif)

### GUI Image
![alt text](images/GUI_ss.png)

A small Windows-friendly UART monitor to **send HEX payloads** and **view received bytes in HEX**.
Made for quick STM32 bring-up / “system mode” testing.

---

## Features

- ✅ GUI built with **Tkinter**
- ✅ Select **COM port** + set **baud rate**
- ✅ **Start / Stop** open/close serial port
- ✅ Send **HEX bytes** like CAN-style payloads  
  - Accepts: `01 0A FF 00` or `010AFF00`  
  - Also accepts `0x` prefix (it gets removed): `0x01 0x0A FF`
- ✅ Logs:
  - `[Transmitted HEX] ...`
  - `[Received Hex] ...`
- ✅ Non-blocking read (polls every ~50 ms)

---

## Requirements

- Python 3.x
- `pyserial`

Install:
```bash
pip install pyserial
````

---

## Run

### Option A — Run directly

From `python_project/`:

```bash
python monitor_uart_gui.py
```

### Option B — Run using the batch launcher (Windows)

Use `run_uart.bat` for one-click run with a venv Python.

1. Open `run_uart.bat`
2. Edit these lines:

   * `VENV_DIR=...`  (your venv folder)
   * `SCRIPT_PATH=...` (full path to `monitor_uart_gui.py`)
3. Double-click `run_uart.bat`

> Note: The `.bat` currently includes placeholders like `...` in one section — you can replace that block with your preferred error message if needed.

---

## How to use

1. Click **Refresh**
2. Select your **COM port**
3. Enter **Baud** (default: `115200`)
4. Click **Start**
5. Type HEX in the Send box and press **Enter** or click **Send**

### Important

The GUI uses Python `bytes.fromhex(...)`.

So:

* Only valid hex characters are allowed: `0-9 A-F`
* Bytes must be properly grouped (two hex chars per byte)

If the hex string is invalid, Python will raise a `ValueError`.

---

## Receive format

Incoming bytes are displayed as:

```
[Received Hex] 01
```

---

## Notes for STM32 side

This tool is best for firmware that expects **raw bytes** on UART.
Example: if STM32 expects a single command byte (`0x00`, `0x01`, `0x02`), send:

* `00`  (toggle LED / mode depending on your firmware)
* `01`
* `02`

---

## Troubleshooting

**No COM port shown**

* Click **Refresh**
* Check USB-UART driver / ST-Link VCP driver
* Try another USB port/cable

**"Access denied" / cannot open port**

* Another program is using the COM port (close CubeIDE terminal, PuTTY, etc.)
* Unplug/replug device

**No received data**

* Check wiring: TX/RX swapped, common GND
* Confirm correct UART instance on STM32 and correct baud rate

---

## File overview

* `monitor_uart_gui.py` → GUI application
* `run_uart.bat` → one-click runner using venv python (no activation needed)

---

## Future improvements (nice-to-have)

* Checkbox: “Send as ASCII with CRLF” (you already have commented code for this)
* Catch invalid HEX input and show a friendly messagebox (handle `ValueError`)
* Optional logging to file



---

# STM32F746ZG – Project Setup (Hardware + Tools)

This repository contains my first “getting started” experiments on the **STM32F746ZG** (e.g., LED blink, basic HAL tests), built and flashed using ST’s official toolchain.

---

## 1) Hardware / Board Documentation

Use these links to understand the board connections (LEDs, buttons, jumpers, ST-LINK), and to find pin mappings:

- **STM32 Nucleo-144 boards (MB1137) – User Manual (UM1974)**  
  Board-level details: LEDs, buttons, solder bridges, connectors, power options, ST-LINK, etc.  
  https://www.st.com/resource/en/user_manual/um1974-stm32-nucleo144-boards-mb1137-stmicroelectronics.pdf

- **ST Wiki – Getting Started with STM32**  
  Step-by-step onboarding: tool installation, first project flow, common setup tips.  
  https://wiki.st.com/stm32mcu/wiki/Category:Getting_started_with_STM32

- **STM32F7 HAL & Low-Layer driver description (UM1905)**  
  Explains HAL/LL driver architecture, APIs, and usage patterns for STM32F7 series.  
  https://www.st.com/resource/en/user_manual/um1905-description-of-stm32f7-hal-and-lowlayer-drivers-stmicroelectronics.pdf

---

## 2) Required Applications

These are the core ST applications used in this project:

### ✅ STM32CubeMX
- **Purpose:** Pin/clock configuration and project code generation  
- **Why it’s useful:** Quickly sets up GPIO/ADC/CAN/UART, clocks, middleware, and generates a clean starting project structure.

> Note: CubeMX can be used standalone or integrated inside CubeIDE (depending on your workflow).

### ✅ STM32CubeIDE
- **Purpose:** Full IDE with GCC toolchain + debug integration  
- **Output:** Builds firmware and produces `*.elf` (and optionally `*.hex` / `*.bin`) for flashing.

### ✅ STM32CubeProgrammer
- **Purpose:** Flash and verify firmware on the target via ST-LINK (SWD)  
- **Typical use:** Load `*.elf` / `*.hex` / `*.bin`, program the MCU, verify, reset/run.

---

## 3) Typical Workflow (Quick Overview)

1. **Configure** (optional but recommended): CubeMX  
   - Choose MCU/board
   - Set pinout, clocks, and peripherals
   - Generate project

2. **Build & Debug**: CubeIDE  
   - Compile the project → generates `*.elf`
   - Debug via ST-LINK (optional)

3. **Flash**: CubeProgrammer  
   - Connect via **ST-LINK / SWD**
   - Program `*.elf` / `*.hex` / `*.bin`
   - Verify + reset to run

---

## 4) Notes / Tips

- If you’re unsure about **LED pins**, always check the **board user manual (UM1974)** first (LEDs and solder bridges can affect which pin is actually used).
- Prefer using **HAL** at the beginning for readability; you can later move to **LL** or register-level code for tighter control.

---

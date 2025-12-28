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

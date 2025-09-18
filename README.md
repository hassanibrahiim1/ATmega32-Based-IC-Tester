# ATmega32-Based IC Tester

**Automated digital IC identification and verification tool**  
Embedded C firmware for ATmega32 that tests digital ICs by driving inputs, reading outputs and validating responses against stored truth tables.

---

## Abstract
This project implements a reliable and extensible Integrated Circuit (IC) tester using the ATmega32 microcontroller. The tester executes predefined test vectors (truth tables) for a variety of common logic ICs, automates pin configuration and validation, and reports the detected IC or error status. The firmware is modular to allow easy addition of new IC definitions and truth tables.

---

## Key Features
- Automated pin initialization and role assignment (input/output).  
- Drives outputs and verifies inputs against truth tables for each IC.  
- Supports multiple logic families (gates, buffers, latches, decoders, counters, parity checkers).  
- Robust retry mechanism and error detection logic.  
- Modular metadata-driven architecture for simple extensibility.  
- Minimal external hardware required (test socket, 5V regulated supply).

---

## Technology Stack
- **Microcontroller:** ATmega32 (AVR)  
- **Language:** Embedded C (AVR-GCC compatible)  
- **Toolchain:** avr-gcc, avr-libc, avrdude (or Atmel Studio/AVRDUDE equivalent)  
- **Optional:** Serial debug over USART for diagnostics

---

## Hardware Requirements (recommended)
- ATmega32 microcontroller (with ISP programming header)  
- 5V regulated power supply (stable, well decoupled)  
- ZIF / IC test socket (24-pin compatible; adapt as required)  
- LEDs (optional) for visual pass/fail indicators  
- USB-to-UART adapter (optional) for serial debug  
- ISP programmer (e.g., USBasp, AVRISP) for flashing

### Recommended components and notes
- 0.1 µF decoupling capacitors near VCC/GND pins.  
- 10k pull-up/pull-down resistors where inputs are floating.  
- Current-limiting resistors for LEDs.  
- Ensure correct VCC/GND orientation before inserting ICs.

---

## Firmware Overview
The firmware uses a metadata array describing each supported IC:

- `ic_name` — human-readable IC identifier (e.g., `"4081"`)  
- `pin_count` — number of relevant pins in test mapping  
- `pins[]` — mapping of socket pins and their roles (`OUTPUT`, `INPUT_FREE`)  
- `truth_table[]` — rows of expected logic values for input/output verification  
- `truth_table_rows` — number of test vectors per IC

At runtime the tester:
1. Initializes pins according to metadata (`init_ic_pins`).  
2. Applies each vector from the truth table to output pins.  
3. Delays for signal settling.  
4. Reads input pins and compares with the expected values (with retries).  
5. If all vectors match, returns the IC name; otherwise returns an error message.

---

## Operation & Test Procedure
1. Power the tester (5V) and ensure the ATmega32 is flashed with the firmware.  
2. Insert the IC correctly into the test socket (observe pin 1 orientation).  
3. Start the test (automatic on power-up or via a test button depending on firmware).  
4. Observe indicators (LED, serial output): the tester will either print the IC name or an error message.

---

## Build & Flash (example)
> These commands assume you have a `Makefile` that produces `main.hex`. Replace the repo/paths as needed.

```bash
# Build (requires avr-gcc and avr-libc)
make

# Flash using avrdude (USBasp example)
avrdude -c usbasp -p m32 -U flash:w:main.hex
If you prefer explicit compilation commands (AVR-GCC toolchain example):

bash
Copy code
avr-gcc -mmcu=atmega32 -Os -Wall -std=gnu11 -I./include -c src/main.c -o main.o
avr-gcc -mmcu=atmega32 -o main.elf main.o ... (other objects)
avr-objcopy -O ihex main.elf main.hex
Serial Debug (optional)
Configure the firmware USART for e.g. 9600 or 115200 bps for debug output.

Example diagnostic output:

csharp
Copy code
[IC-TESTER] Running test...
[IC-TESTER] Applying vector 1/4
[IC-TESTER] Read inputs: 0b001 -> expected 0b001
[IC-TESTER] IC detected: 4081
Example Supported ICs (non-exhaustive)
4081 — AND gate

7486 — XOR gate

74541 — Buffer / Line driver

744511 — BCD to 7-seg decoder

4043 — SR latch

74280 — Parity generator/checker

74196 — Synchronous counter

Adding a New IC
Create an ICMetadata_t entry with ic_name, pin_count, pins[] mapping and truth_table[].

Add the new entry to the ic_metadata array and update NUM_ICS if necessary.

Rebuild and flash firmware.

Test with a known-good IC to verify correctness.

Troubleshooting
No response / unknown: Check power rails, socket orientation, and pin wiring.

Intermittent mismatch: Add small delays for signal settling, verify pull-ups/pull-downs.

Flashing fails: Ensure correct programmer, correct mcu param for avrdude, and that fuses are appropriate.

False negatives: Verify truth table order and pin mapping (common source of errors).

Future Work / Improvements
Add auto-detection for pin mapping or support for multiple package types.

Add a small LCD/OLED display to show detected IC and diagnostic info.

Implement a serial/USB protocol to log test results to a PC.

Add more IC families, timing-sensitive tests, and analog-level checks.

License
This project is provided under the MIT License — see LICENSE for details.

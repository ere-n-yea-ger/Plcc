8051 PLCC Supervisory Card - DUART Serial Diagnostics

Overview

This repository contains the diagnostic firmware and source code used to isolate, debug, and verify physical layer serial communication (RS-232) on a legacy telecom PLCC Supervisory Board.

The objective of this project was to bypass complex background telecom tasks (LCD initialization, DTMF processing) and isolate a silent serial transmission issue by interacting directly with the external memory-mapped DUART chip.

Hardware Architecture

Microcontroller: Atmel AT89S52 (8051 core)

System Clock: 11.0592 MHz Crystal

Serial Controller: 2681 / 68681 DUART (Dual Universal Asynchronous Receiver-Transmitter)

Memory Mapping: DUART is mapped to External RAM (XDATA) starting at address 0x9600.

Firmware Storage: AMD AM29F002NT Flash ROM (Programmed via BPWin).

The Diagnostic Protocol: The "Screaming U"

To determine if the silent terminal was caused by software logic or physical hardware faults (e.g., broken RS-232 line drivers, bent socket pins, or hardware Watchdog Timer resets), I engineered a minimalist hardware diagnostic loop.

The program initializes the baud rate generator (9600 Baud, 8N1) and continuously pushes the hexadecimal value 0x55 (ASCII 'U') to the DUART. 0x55 translates to a binary 01010101, which creates a perfect square wave on an oscilloscope to test physical line integrity.

The Bug Hunt: Fixing the Closed Hardware Valve

During code auditing and simulator memory inspection, I discovered that the legacy InitDUART() sequence was missing a critical command word. The registers were being reset, but the physical Transmit and Receive gates inside the silicon were never enabled.

The Fix:
I patched the initialization sequence to explicitly write 0x05 to Command Register A (CRA).

// Enable Transmitter (Bit 2) and Receiver (Bit 0)
// This connects the internal holding registers to the physical TXD/RXD pins.
DUART_CRA_ADDR = 0x05; 


Keil XDATA Simulator Verification

Before burning the physical ROM, the memory bus logic was verified using the Keil $\mu$Vision XDATA logic simulator.

By observing address 0x9600, I verified the exact byte sequence hitting the external hardware bus:

0x9600 (Mode Reg): 07 (8N1 Framing)

0x9601 (Clock Reg): BB (9600 Baud)

0x9602 (Command Reg): 05 (TX/RX Enabled)

0x9603 (Transmit Reg): 55 (ASCII 'U' data payload)

Conclusion & Physical Layer Dependencies

Through this diagnostic code, I successfully proved the 8051 logic and memory bus routing were 100% functional. When run on physical hardware, the resulting behavior (a blocked signal vs. a successful stream) allows hardware technicians to immediately narrow faults down to board-specific dependencies, such as un-kicked Hardware Watchdog Timers or disabled RS-232 Line Driver ICs (e.g., MAX232).

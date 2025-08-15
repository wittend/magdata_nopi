# magdata_nopi

A lightweight data acquisition tool for the PNI RM3100 3‑axis magnetometer and MCP9808 temperature sensors on Linux SBCs (e.g., Raspberry Pi). It timestamps samples, can align to a PPS (pulse-per-second) signal, and emits compact JSON lines for easy downstream consumption.

Key features
- Magnetometer sampling in polling or continuous modes
- Configurable cycle counts per axis (affects gain/sensitivity)
- Configurable sampling rate via the device’s timing register
- Local/remote MCP9808 temperature readings
- Optional PPS synchronization on GPIO 27 (pin 36) for precise timing
- Output as one JSON line per sample to stdout or to named pipes

Supported hardware (typical)
- PNI RM3100 magnetometer on I2C
- MCP9808 temperature sensors (local and/or remote) on I2C
- Optional GPS PPS wired to GPIO 27 (physical pin 36)

Prerequisites
- Linux with I2C enabled (e.g., Raspberry Pi OS)
- Toolchain: CMake and a C compiler (GCC/Clang)
- I2C userspace support (i2c-dev module)
- GPIO/I2C userland library/daemon (e.g., pigpio daemon or compatible variant). The project supports remote/daemon-style operation.

Quick start
1) Enable I2C on your system:
- Raspberry Pi: run sudo raspi-config → Interface Options → I2C → Enable, then reboot.
- Verify with: sudo i2cdetect -y 1

2) Install dependencies (Debian/Raspberry Pi OS):
- sudo apt update
- sudo apt install -y cmake build-essential pigpio libi2c-dev

3) Start the GPIO daemon (if using pigpio-style operation):
- sudo systemctl enable pigpiod
- sudo systemctl start pigpiod
  or: sudo pigpiod

4) Build:
- cmake -S . -B build
- cmake --build build -j

5) Run (examples):
- Polling mode with default settings:
  ./build/magdata_nopi
- Set cycle counts and remain in polling mode:
  ./build/magdata_nopi -c 400 -g 0
- Set device timing register value (sampling rate related):
  ./build/magdata_nopi -D 0x96
- Show version and exit:
  ./build/magdata_nopi -V

Notes:
- The actual binary name may differ depending on your build system configuration. Inspect the build output for the produced executable.
- For PPS synchronization, wire your GPS PPS signal to GPIO 27 (pin 36) and ensure proper electrical levels.

Output format
Each sample is emitted as a JSON object on a single line, for example:
{ "ts":"10 Aug 2025 12:34:56", "lt":23.25, "rt":24.12, "x":123.456, "y":-78.900, "z":10.123 }

Fields:
- ts: UTC timestamp
- lt: Local temperature in °C (MCP9808), or 0.0 if invalid
- rt: Remote temperature in °C (MCP9808), or 0.0 if invalid
- x, y, z: Magnetic field components (units depend on configured scaling; see USAGE)

Documentation
- docs/USAGE.md — command-line options, examples, and output schema details
- docs/HARDWARE.md — wiring, addressing, and enabling I2C/PPS
- docs/ARCHITECTURE.md — modules, runtime flow, and design notes
- docs/TROUBLESHOOTING.md — common issues and fixes

License
- GPL-3.0

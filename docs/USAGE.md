# Usage

This program acquires magnetic field data (RM3100) and temperatures (MCP9808) and prints one JSON line per sample. It supports polling and continuous modes, configurable cycle counts, and a sampling rate setting via the device timing register.

Command-line options
- -B <mask>
  Request built-in self-test (BIST) with a bitmask. Placeholder in current builds.
- -C
  Read back cycle count registers before sampling (diagnostic).
- -c <count>
  Set cycle counts for X/Y/Z axes to the same value (e.g., 200 or 400). Cycle count influences measurement scale/gain.
- -D <rate>
  Set sampling related timing register value (TMRC). Refer to the RM3100 datasheet for valid mappings between register values and effective sampling rates.
- -g <mode>
  Sampling mode: 0 = POLL (default), 1 = CONTINUOUS (CMM).
- -V
  Print version and exit.
- -h or -?
  Show help.

Examples
- Default polling mode:
  ./build/magdata_nopi
- Increase cycle count to 400 for all axes:
  ./build/magdata_nopi -c 400
- Set timing register value (TMRC) to 0x96:
  ./build/magdata_nopi -D 0x96
- Enable cycle count readback for diagnostics:
  ./build/magdata_nopi -C
- Print version:
  ./build/magdata_nopi -V

Output schema
Each output line is a compact JSON object:
{ "ts":"%d %b %Y %T", "lt":<float>, "rt":<float>, "x":<float>, "y":<float>, "z":<float> }

- ts: UTC timestamp string (e.g., "10 Aug 2025 12:34:56")
- lt: Local temperature in degrees Celsius (MCP9808). If an error occurs, 0.0 is reported.
- rt: Remote temperature in degrees Celsius (MCP9808). If an error occurs, 0.0 is reported.
- x, y, z: Magnetic field components. The absolute units depend on your configured cycle counts and scaling. For consistent physical units, keep cycle counts constant and apply a downstream calibration/scaling based on your setup.

Exit codes
- 0: Normal termination
- 1: Temperature sensor initialization failure
- 2: PPS timeout or magnetometer init/verify failures (see messages)

Pipes (optional)
The program can be integrated with named pipes (FIFOs) to feed data to other processes. When enabled at build/runtime, the tool writes the same JSON lines to the configured output FIFO and may accept control from an input FIFO. See docs/HARDWARE.md for creating FIFOs and permissions, and your build configuration for enabling pipe support.

Performance tips
- Use PPS on GPIO 27 when precise timing alignment is required.
- Higher cycle counts increase measurement resolution but also increase conversion time; adjust sampling rate accordingly.
- Ensure good I2C wiring practices to avoid NACKs and bus errors at higher rates.

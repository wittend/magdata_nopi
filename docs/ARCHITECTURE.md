# Architecture

Purpose
A single-process data acquisition application that:
- Initializes I2C-connected sensors (magnetometer and temperature sensors)
- Optionally configures PPS synchronization
- Periodically reads sensors (either polling or continuous modes)
- Formats and emits JSON lines suitable for logging or streaming pipelines

Major components
- Entry point and orchestration: initialization, main loop, shutdown
- Configuration/state struct: carries runtime options, handles, addresses, gains, and timing information
- Command-line manager: parses options, validates inputs, and shows settings
- Magnetometer helpers: set/get sampling rate, compute gains from cycle counts, manage measurement modes
- I2C helpers: minimal wrappers for register/block I/O via userspace I2C

Runtime flow
1) Parse command-line options and initialize defaults
2) Initialize GPIO/I2C subsystem (connect to GPIO daemon if applicable)
3) Open I2C handles for RM3100 and MCP9808 sensors
4) Verify magnetometer presence/version
5) Initialize sensor configuration (cycle counts, timing register, mode)
6) Optionally set up PPS edge detection callback on GPIO 27
7) Main loop:
   - On each cycle (or PPS edge), read temperatures and magnetometer
   - Apply any configured delays
   - Compute scaled values and write a single JSON line to output
8) On termination, close I2C handles, stop GPIO daemon connection, and exit

Sampling modes
- POLL: Explicitly trigger and read measurements each cycle
- CONTINUOUS (CMM): Sensor runs continuously; the program reads when data-ready is asserted

Scalability and integration
- Output is line-delimited JSON, enabling simple composition with tools like jq, log processors, or custom consumers.
- Named pipes can be used to connect to web servers, dashboards, or long-running loggers without additional sockets.

Extensibility guidelines
- Keep hardware-specific constants centralized.
- Add new output fields cautiously to preserve downstream compatibility.
- Consider a structured config file for complex deployments; retain command-line overrides for quick tests.

# Hardware and System Setup

Overview
- The tool reads an RM3100 3‑axis magnetometer and up to two MCP9808 temperature sensors over I2C.
- Optional GPS PPS (pulse-per-second) on GPIO 27 (Raspberry Pi physical pin 36) can be used to align sampling to second boundaries.

I2C wiring (typical)
- Bus: Raspberry Pi I2C bus 1 (SDA = GPIO 2, SCL = GPIO 3)
- Pull-ups: Ensure SDA/SCL have 3.3V pull-ups (most breakout boards include these)
- Power: 3.3V logic level. Do not connect 5V signals to GPIO or I2C pins.

Addresses (typical)
- MCP9808 default address is often 0x18; check your board’s solder pads/jumpers for address selection if using multiple sensors.
- RM3100 I2C address depends on the board/module configuration; consult the module’s documentation.

PPS wiring (optional)
- PPS input: GPIO 27 (pin 36) on Raspberry Pi headers.
- Electrical levels: 3.3V tolerant. Use a proper level shifter if your GPS outputs 5V PPS.
- Ground: Common ground between GPS and the SBC.

Enable I2C on the OS
- Raspberry Pi OS:
  - sudo raspi-config → Interface Options → I2C → Enable → Reboot
  - Verify: sudo i2cdetect -y 1
- Ensure the i2c-dev kernel module is loaded: lsmod | grep i2c_dev

GPIO daemon/service
- If using a daemon-backed GPIO/I2C approach, start the daemon on boot:
  - sudo systemctl enable pigpiod
  - sudo systemctl start pigpiod
  - Or run manually: sudo pigpiod

Creating FIFOs (optional)
- To integrate with other processes, create named pipes:
  - mkfifo /path/to/magdata.fifo
  - mkfifo /path/to/magctl.fifo
- Ensure file permissions allow the data producer and consumer to access these FIFOs.

Grounding and noise considerations
- Place the RM3100 away from ferromagnetic materials and switching regulators.
- Use twisted pairs or shielded cable for longer I2C runs; keep bus length reasonable.
- Keep PPS wiring short and clean to reduce jitter.

Safety
- Double-check voltage levels before connecting devices.
- Power down the system when changing wiring.

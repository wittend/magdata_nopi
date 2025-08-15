# Troubleshooting

No I2C devices found
- Check I2C is enabled in the OS (raspi-config)
- Verify wiring and pull-ups; run: sudo i2cdetect -y 1
- Confirm correct bus number (commonly 1 on Raspberry Pi)

Cannot connect to GPIO daemon
- Ensure the daemon is running: sudo systemctl status pigpiod
- Start it: sudo systemctl start pigpiod or sudo pigpiod
- Check user permissions; try running with sudo to isolate permission issues

Magnetometer revision mismatch
- The tool validates a device revision register. If you see a mismatch, confirm:
  - The I2C address matches your RM3100 module configuration
  - SDA/SCL lines are connected and stable
  - No address conflict with other devices on the bus

Temperature read failures / invalid temperature (0.0)
- Check sensor address selection (jumpers/solder pads)
- Inspect wiring and power
- Probe with i2cdetect and read a known register using a tool like i2cget for diagnosis

PPS not detected
- Verify PPS wired to GPIO 27 (pin 36) and common ground
- Confirm voltage level is 3.3V compatible
- Some GPS modules require enabling PPS output via a separate configuration command (e.g., through serial NMEA or vendor tools)

High noise or unstable readings
- Increase distance from motors, transformers, and ferrous enclosures
- Increase cycle count for higher resolution (at the cost of conversion time)
- Reduce I2C speed if experiencing NACKs or bus errors

JSON parsing issues downstream
- Each line is a complete JSON object; ensure consumers read line-by-line
- Handle floating-point precision and potential “0.0” placeholders for invalid temperatures

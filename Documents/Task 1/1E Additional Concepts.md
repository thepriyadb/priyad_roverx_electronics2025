## Additional Concepts

1. Open-drain driver: Device can pull the bus line LOW, but cannot drive it HIGH. The line goes HIGH only through an external pull-up resistor. This makes I2C multi-master and bidirectional as any device can pull the line LOW without contention.
   Inside the microcontroller or I2C device, the output driver is often a MOSFET transistor.
   When ON, the transistor connects the line to ground -> signal = LOW (0 V).
   When OFF, the transistor diconnects, and the pull-up resistor pulls the line to Vcc (usually 3.3V or 5V) -> signal = HIGH.
2. Drivers: In digital communication, driver refers to the circuit or circuitry inside a chip that is responsible for:
	   - Driving a logic signal onto a bus = Output driver
	   - Receiving or sensing a logic signal from a bus = Input buffer/ Input driver
	Output driver: Controls voltage on a communication line
	(e.g., SDA, SCL)
	Input driver: Reads voltage level to detect logic 1, 0.
3. Electrical timing: In digital communication, *rise time* is how fast a signal goes from LOW (0) to HIGH (1), and *fall time* is how fast it goes from HIGH (1) to LOW (0). 
4. Why do we need stronger drivers in Fast-Mode Plus?
   In I2C communication speed 1 Mbps, signals must rise and fall extremely fast ( within 120 ns ). 
   The output driver (MOSFET) sinks current from the line to pull it LOW. To do this faster, it must turn on quicker, handle more current, have lower ON resistance.
   The pulling line HIGH is done passively via a resistor. To rise faster, we use a smaller resistor because small resistor = more current must be sunk when pulling LOW -> driver must be stronger (handle more current).
   If driver is weak, line will not go LOW quickly enough and the rise time will be too slow, causing timing violations, misinterpretation of bits, and communication failure.
5. In the High-speed (3.4 Mbps) mode, the controller device must first use a controller code to allow for high-speed data transfer. Why is this so?
   Communication cannot start directly at 3.4 Mbps. Instead it must first begin in a lower speed mode (Standard/ Fast). The controller (master device) starts communication using Standard/ Fast mode rules. It then sends a special 8-bit code called Hs-mode master code, which is 00001XXX, where 00001 prefix identifies it as a high-speed enabling command and the XX bits can define multiple masters. No ACK is required from the slave, it just recognizes the code and shifts into a High-speed Mode.
   This is required to ensure backward compatibility with older I2C devices that don't support Hs-mode. 
   After receiving the Hs-mode master code, all target devices that support Hs-mode switch their internal I2C hardware to Hs-mode. Now the controller begins transmitting data at up to 3.4 Mbps. Timing rules now follow Hs-mode specifications. 
6. What is OSI model?
   It is a conceptual framework that organizes network communications into 7 layers which contains physical, data link, network, transport, session, presentation, application layers.
   
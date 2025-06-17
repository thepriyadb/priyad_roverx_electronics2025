Some terms:

### **Voltage (Operating Logic Level)**
The voltage used for HIGH signals on GPIOs.
### **USB Type**
The USB Type is the physical connector used to upload code and power the board. Different types vary in size, strength, and modernity. USB type doesn’t affect data speed.

### **UART - Universal Asynchronous Receiver Transmitter**
- UART is a serial communication method where data is sent one bit at a time, asynchronously (no clock signal).
- It uses 2 wires:
    - TX → Transmit
    - RX → Receive
- Used in Bluetooth, GPS
### **PWM pins**
- Used to output fake analog voltages by turning ON/OFF really fast.
- Work with analogWrite(), takes values from 0 to 255.
- Great for dimming LEDs or controlling motor speed.
### **Analog pins**
- Used to read voltage from analog sensors (like potentiometers, temperature sensors).
- Work with analogRead(), gives value from 0 to 1023.
- Input only, you can’t output analog voltages through them.
### **Digital I/O**
- Physical pins
- Input = HIGH/LOW - button, sensor
- Output = HIGH/LOW - LED, buzzer
### **EEPROM**
- Electrically Erasable Programmable Read-Only Memory
- Non-volatile memory used to store data permanently even after power loss.
### **SRAM**:
- Static Random Access Memory
- Volatile - used during programs execution.
- Where real time processing happens.
### **Flash Memory**: 
- Non-volatile memory to store your program, like the code we upload.
- Readable + Writable
- More flash memory = More code & complexity the MCU can handle
- Smaller flash = low power, cost, simpler boot process.
- Larger flash = more complexity, more power usage.
### **Clock Speed**: 
- How fast microcontroller executes instructions. It’s measured in MHz.
- Higher clock = faster processing = faster responses.
- Slow clock like 16MHz -> Low power usage, slow speed.
- Fast clock like 240MHz -> Need good power management, fast data handling.

Core Architecture: The core is the processing unit architecture which is like the language and brain style the MCU uses to run code.

| **Feature**          | **Arduino Uno R3** | **Arduino Nano** | **Arduino Mega 2560** | **STM32F103C8T6** | **STM32 Nucleo-F446RE** | **ESP32 DevKit v1** |
| -------------------- | ------------------ | ---------------- | --------------------- | ----------------- | ----------------------- | ------------------- |
| **Core**             | ATmega328P         | ATmega328P       | ATmega2560            | Cortex-M3         | Cortex-M4               | Xtensa Dual-core    |
| **Clock<br>Speed**   | 16 MHz             | 16 MHz           | 16 MHz                | 72 MHz            | 180 MHz                 | 240 MHz             |
| **Flash**            | 32 KB              | 32 KB            | 256 KB                | 64 KB             | 512 KB                  | 4 MB                |
| **SRAM**             | 2 KB               | 2 KB             | 8 KB                  | 20 KB             | 128 KB                  | 520 KB              |
| **EEPROM**           | 1 KB               | 1 KB             | 4 KB                  | None              | Optional                | Yes (emulated)      |
| **Digital I/O**      | 14                 | 14               | 54                    | ~37               | ~76                     | ~34                 |
| **Analog<br>Inputs** | 6                  | 8                | 16                    | 10                | 16                      | 18                  |
| **PWM Pins**         | 6                  | 6                | 15                    | 12+               | 12+                     | All (via timer)     |
| **UART**             | 1                  | 1                | 4                     | 2                 | 3                       | 3                   |
| **I2C**              | 1                  | 1                | 1                     | 2                 | 3                       | 2                   |
| **SPI**              | 1                  | 1                | 1                     | 2                 | 3                       | 4                   |
| **USB Type**         | USB-B              | Mini-USB         | USB-B                 | Micro-USB         | Micro-USB               | Micro-USB           |
| **Voltage**          | 5V                 | 5V               | 5V                    | 3.3V              | 3.3V                    | 3.3V                |
| **IDE**              | Arduino IDE        | Arduino IDE      | Arduino IDE           | STM32Cube         | STM32Cube               | MicroPython         |

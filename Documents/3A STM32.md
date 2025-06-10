_STM32_??

STM32 is a family of _32-bit ARM Cortex-M microcontrollers_ by STMicroelectronics. Unlike Arduino boards, STM32 MCUs are more powerful, have more features, and are used in professional/industrial systems.

STM32 boards (like the Blue Pill) allow precise control of hardware using low-level programming and libraries like STM32 HAL or direct register access.

---
### _Microcontroller Core_:
STM32 MCUs use ARM Cortex-M cores (e.g., M0, M3, M4, M7):
- STM32F1 → Cortex-M3
- STM32F4 → Cortex-M4 (with DSP/FPU)
- STM32G0 → Cortex-M0+
- STM32H7 → Cortex-M7 (high performance)
These offer:
- 32-bit data paths
- Fast execution
- Lower power consumption than 8-bit MCUs
---
### _Microcontroller Function_:

The STM32 MCU acts as the central processor:
- Reads inputs (from GPIO, ADC, UART, etc.)
- Processes logic (using user-written code in C/C++)
- Sends outputs (PWM, UART, SPI, I2C, DAC, GPIO)
- Interacts with real-time events using NVIC (interrupt controller)

---

### GPIO Pins:

GPIO = General Purpose Input/Output.
- STM32F103C8T6 has GPIO Ports A, B, C, etc. (16 pins per port)
- Each GPIO pin can be individually:
    - Input, Output, Alternate Function, Analog
    - Pull-up, Pull-down, Floating, or Open Drain
Pin functions are configured using **GPIO registers** or HAL library.

---

### _Memory Structure_:

STM32 MCUs have 3 major memory types:
- **Flash memory**: Non-volatile; stores user code (up to 64 KB in Blue Pill).
- **SRAM**: Volatile; stores variables during execution (up to 20 KB).
- **EEPROM**: Not present natively, but Flash can be used as emulated EEPROM.

---

### STM32 IDEs:

- **STM32CubeIDE** (official) – includes code editor, compiler, debugger.
- **Keil MDK**, **IAR Embedded Workbench** – popular professional IDEs.
- **PlatformIO**, **Arduino IDE** (via STM32 core) – easier alternatives.

---

### STM32CubeMX:

Graphical tool to configure:
- Pin mapping
- Clock setup
- Middleware (USB, RTOS)
- Generate initialization C code

---

### _Communication Protocols_:

STM32 supports multiple hardware communication interfaces:
- **UART/USART**: Serial communication (TX/RX)
- **I2C**: Interfacing sensors/modules (SDA/SCL)
- **SPI**: Fast data transfer (MOSI, MISO, SCLK, NSS)
- **CAN**: For industrial/motor systems
- **USB**: STM32 can act as USB Device or Host
- **LIN, I2S, SDIO**: Supported in specific variants

DMA (Direct Memory Access) is often used to offload data transfer from CPU.

---

### _Timers_:

Timers in STM32 are very advanced:
- **Basic Timers (TIM6, TIM7)** – for delays
- **General Purpose Timers (TIM2-TIM5)** – for PWM, encoder, capture/compare
- **Advanced Timers (TIM1, TIM8)** – for motor control (center-aligned PWM)

Timer features:
- Prescaler, auto-reload, counter direction
- PWM generation
- Input capture (for frequency/time)
- Output compare
- Interrupts

---

### PWM in STM32:

PWM is generated using timers.
- Each timer has multiple **channels**
- Output is available on Alternate Function pins
- Fine control over frequency and duty cycle

---

### _Analog Features_:

- **ADC** (Analog-to-Digital Converter):
    - 12-bit (0–4095)
    - Multiple channels (e.g., 10 in STM32F103)
    - Can run in DMA or interrupt mode
- **DAC** (Digital-to-Analog Converter): Converts digital value to analog voltage (available in higher STM32 families)

---

### _Clock System_:

STM32 uses internal and external clocks:

- **HSI**: Internal 8 MHz
- **HSE**: External crystal (8–25 MHz)
- **PLL**: Used to multiply frequency (to get 72 MHz system clock)
- Clock tree configuration is done using RCC (Reset and Clock Control)

Accurate clock settings are vital for USB, ADC, UART baud rate, etc.

---

### _Boot Modes_:

STM32 has 3 boot options via BOOT0 and BOOT1 pins:

- **Main Flash**: normal program
- **System memory**: DFU bootloader (for USB/serial programming)
- **SRAM**: for debugging

---

### _Interrupts and NVIC_:

STM32 has Nested Vectored Interrupt Controller (NVIC):

- Supports prioritizing multiple interrupts
- Fast, deterministic ISR handling
- Each peripheral can trigger its own interrupt

---

### _Power Modes_:

STM32 supports multiple low-power modes:

| Mode    | CPU | Peripherals | Wake-up Source              |
| ------- | --- | ----------- | --------------------------- |
| Sleep   | ON  | ON          | Any interrupt               |
| Stop    | OFF | Some        | External/RTC/USART          |
| Standby | OFF | OFF         | Reset or external interrupt |

Used in battery-powered IoT devices to extend life.

---

### _Bootloader & Firmware_:

- STM32 includes a **factory ROM bootloader** in system memory.
- No external programmer needed (uses USB/Serial/DFU)
- Firmware is flashed using:
    - STM32CubeProgrammer
    - DFU tools
    - Serial bootloader (USART1)

---

### _Watchdog Timers_:

- **IWDG (Independent WDT)**: Uses separate RC oscillator.
- **WWDG (Window WDT)**: Needs refreshing within a time window.

Prevents lock-ups by auto-resetting the system if software hangs.

---

### _Bit Manipulation & Registers_:

Unlike Arduino, STM32 allows direct register access:

Used for:
- Speed
- Real-time control
- Hardware-specific tweaking

---

### _Fuses & Option Bytes_:

- STM32 doesn’t have fuses like AVR, but uses _Option Bytes_:
    - Configure read protection
    - Select boot memory        
    - Control WDT behavior        
    - Can be changed via STM32CubeProgrammer        

---

### _RTOS Support_:

STM32 supports FreeRTOS and other real-time operating systems.  
Use cases:
- Multitasking (e.g., running motor + sensor + display)
- Better timing and scheduling than bare loops

---

### _Debugging Interface_:

- SWD (Serial Wire Debug): 2-pin ARM debugging    
- JTAG: More advanced multi-wire debugging    
- Compatible with ST-Link, J-Link, or CMSIS-DAP probes    

---

### _STM32 vs Arduino Uno_ :

| **Feature**           | **STM32F103C8T6**                                                                                                                                                                                                                | **Arduino Uno (ATmega328P)**                                                                                                          |
| --------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------- |
| **Architecture**      | 32-bit ARM Cortex-M3 - Modern 32-bit RISC architecture                                                                                                                                                                           | 8-bit AVR - Simpler 8-bit RISC architecture                                                                                           |
| **Clock Speed**       | 72 MHz - Enables complex computation, faster data handling, higher-speed peripheral operation.                                                                                                                                   | 16 MHz - Standard speed for basic microcontrollers; slower data processing.                                                           |
| **Flash Memory**      | 64 KB - More space for complex programs                                                                                                                                                                                          | 32 KB - Sufficient smaller to medium programs                                                                                         |
| **SRAM**              | 20 KB                                                                                                                                                                                                                            | 2 KB - Limited                                                                                                                        |
| **EEPROM**            | Not typically integrated - Most STM32F1 series lack on-chip EEPROM. External EEPROM required for non-volatile data storage.                                                                                                      | 1 KB - Dedicated EEPROM for non-volatile data storage without consuming Flash.                                                        |
| **ADC Resolution**    | 12-bit                                                                                                                                                                                                                           | 10-bit                                                                                                                                |
| **Communication**     | UART, I2C, SPI, CAN - CAN useful for automotive, industrial control. Multiple UARTs (USARTs), SPIs, I2Cs.                                                                                                                        | UART, I2C, SPI - Single UART, SPI, I2C.                                                                                               |
| **Timers**            | Advanced & General - Multiple versatile timers. Includes advanced control timers (e.g., motor control, complementary outputs, dead-time insertion) and general-purpose timers (timing, counting, PWM, quadrature encoder input). | 3 timers - Typically two 8-bit, one 16-bit timer. Primarily for basic timing, counting, simple PWM generation.                        |
| **PWM Channels**      | Multiple via timers - Allows various duty cycles, frequencies, synchronized outputs.                                                                                                                                             | 6 (fixed pins) - Provides 6 PWM outputs on specific digital pins.                                                                     |
| **Power Consumption** | Lower in low-power - Sophisticated power management modes (sleep, stop, standby) enable very low consumption; crucial battery-powered, IoT applications.                                                                         | Higher - Generally consumes more power, less ideal for energy-critical, long-term battery applications. Includes several sleep modes. |
| **IDE**               | STM32CubeIDE, Keil , STM32CubeIDE                                                                                                                                                                                                | Arduino IDE                                                                                                                           |
| **GPIO Count**        | ~37 - Generally higher number of general-purpose input/output pins. Many pins 5V-tolerant.                                                                                                                                       | ~23 - Fewer GPIO pins, limiting number of direct connections.                                                                         |
| **Voltage Range**     | 2.0V - 3.6V - Operates lower voltage range, common for modern low-power electronics.                                                                                                                                             | 1.8V - 5.5V - Wider operating voltage range, commonly used at 5V for robust signal levels.                                            |

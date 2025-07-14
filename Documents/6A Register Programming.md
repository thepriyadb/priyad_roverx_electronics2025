## Project 9: **Blinking an LED using Port Manipulation**
void setup() {
  DDRB |= (1 << PB1); // Set PB1 (Pin 9) as output
}        
void loop() {
  PORTB |= (1 << PB1);  // Turn LED ON
  delay(500);
  PORTB &= ~(1 << PB1); // Turn LED OFF
  delay(500);
}
## **Register Programming to generate a PWM wave on a single LED**

//constant pwm output

void setup() {
  DDRD |= (1 << DDD6); 
  // Fast PWM Mode: WGM01 = 1, WGM00 = 1 → Mode 3
  TCCR0A = (1 << WGM00) | (1 << WGM01);
  // Non-inverting mode -> COM0A1 = 1 => clears OC0A 
  TCCR0A |= (1 << COM0A1);
  // Prescaler = 64 → PWM freq ≈ 976 Hz
  TCCR0B = (1 << CS01) | (1 << CS00);
  OCR0A = 128;  // 50% Duty Cycle
}

Note: PWM frequency = f_internal_clock / (Prescaler Value* (Top+1))
##### What is OC1A?
- It stands for **Output Compare pin A of Timer1**
- This is **Pin 9 on Arduino UNO**
- The timer hardware can **toggle this pin automatically** when a compare match happens (no manual code needed)
##### What is a compare match?
A **compare match** is when the **timer's current value equals** the value in the compare register.

##### What is WGM?
- `WGM` stands for **Waveform Generation Mode**.
- These are bits inside the **TCCRnA** and **TCCRnB** control registers of a timer.
- They tell the timer **what kind of wave or counting style** you want.

Where are WGM bits?
For **Timer1** (16-bit timer), you have **4 WGM bits**:

| Bit Name | Location      |
| -------- | ------------- |
| WGM10    | TCCR1A, bit 0 |
| WGM11    | TCCR1A, bit 1 |
| WGM12    | TCCR1B, bit 3 |
| WGM13    | TCCR1B, bit 4 |
Together they form a **4-bit number**:  
**WGM13:WGM12:WGM11:WGM10**
This 4-bit number decides **the mode**. For example:
- `0000` (0): Normal mode
- `1110` (14): Fast PWM with ICR1 as TOP
- `0100` (4): CTC mode (Clear Timer on Compare Match)
You write these bits to choose:
- **Normal mode** → just counts from 0 to max
- **PWM mode** → creates wave signals
- **CTC mode** → counts up to a match value, then resets
##### Example: Setting Fast PWM Mode 14
TCCR1A |= (1 << WGM11);      // Set WGM11 = 1
TCCR1A &= ~(1 << WGM10);     // Clear WGM10 = 0
TCCR1B |= (1 << WGM12);      // Set WGM12 = 1
TCCR1B |= (1 << WGM13);      // Set WGM13 = 1
## **Register Programming to generate a PWM wave**

##### Why Do We Use `|` and `&` in Register Programming?
Registers like `PORTB`, `DDRB`, etc. are **8-bit values**.  
Each bit controls a specific **pin** on a port.
We use **bitwise operators** to:
- **Turn ON** a specific bit (without affecting others) → use `|`
    00000000   (PORTB)
|       00000010   (bitmask)
-----------
	00000010   (result)

- **Turn OFF** a specific bit (without affecting others) → use `&` with `~`
    00000010   (PORTB)
&     11111101   (mask with bit 1 cleared)
-----------
    00000000

##### Common Registers
| Register           | Meaning                                                                              |
| ------------------ | ------------------------------------------------------------------------------------ |
| `TCCRnA`           | Timer/Counter Control Register A                                                     |
| `TCCRnB`           | Timer/Counter Control Register B                                                     |
| `OCRnA` / `OCRnB`  | Output Compare Register A/B – sets the duty cycle                                    |
| `ICRn`             | Input Capture Register – sets the TOP value (i.e., period of PWM)                    |
| `TCNTn`            | Timer Counter – the current value of the timer                                       |
| `COMnA1`, `COMnA0` | Compare Output Mode bits – how PWM pin behaves                                       |
| `WGMn3:0`          | Waveform Generation Mode bits – selects PWM mode (e.g., Fast PWM, Phase Correct PWM) |
| `OCnA` / `OCnB`    | Output Compare Pin – the actual pin where PWM signal appears (like Pin 9 = OC1A)     |
## **Registers**
A register in a microcontroller like the ATmega328P (used in Arduino UNO) is a dedicated, high-speed memory location mapped to specific hardware functions such as digital I/O control, timers, ADC, and PWM generation.
Registers like (Where **x** can be **B**, **C**, or **D**.)
- *DDRx* (Data Direction Register) determine whether each pin on a port (e.g., PORTB, PORTD) is configured as *input (0) or output (1)* by toggling specific bits. 
- *PORTx* registers are output latches used to write digital *HIGH or LOW* to output pins.
- *PINx* registers are input buffers used to read the current voltage level from input pins. 
Each bit in a register maps directly to a microcontroller pin (e.g., PB1 is bit 1 of PORTB, controlling Arduino pin 9).
Registers differ from general-purpose memory like SRAM (for variables) or EEPROM (for long-term storage) because they don’t store user data, they directly reflect and control physical hardware behavior. Since registers are located in I/O memory space, they can be accessed in a single CPU clock cycle, making them orders of magnitude faster than standard memory. This makes them critical for tasks like precise PWM generation, fast pin toggling, and interrupt handling.
Unlike digitalWrite or pinMode, which involve multiple instruction cycles and abstraction layers, register access allows bit-level manipulation using operations like (PORTB |= (1 << PB1)), enabling nanosecond-level control.

| **PORT Name** | **Atmega328P Pin** | **Arduino Pin** |
| ------------- | ------------------ | --------------- |
| **PORTD**     | PD0                | D0              |
|               | PD1                | D1              |
|               | PD2                | D2              |
|               | PD3                | D3              |
|               | PD4                | D4              |
|               | PD5                | D5              |
|               | PD6                | D6              |
|               | PD7                | D7              |
| **PORTB**     | PB0                | D8              |
|               | PB1                | D9              |
|               | PB2                | D10             |
|               | PB3                | D11             |
|               | PB4                | D12             |
|               | PB5                | D13             |
| **PORTC**     | PC0                | A0              |
|               | PC1                | A1              |
|               | PC2                | A2              |
|               | PC3                | A3              |
|               | PC4                | A4              |
|               | PC5                | A5              |

## **Classification Of Registers:**

| Type                        | Example Registers                                    | Purpose                                                                                                        |
| --------------------------- | ---------------------------------------------------- | -------------------------------------------------------------------------------------------------------------- |
| **I/O Control Registers**   | `DDRx`, `PORTx`, `PINx`                              | Directly control digital pins (input/output, HIGH/LOW, read status).                                           |
| **Timer/Counter Registers** | `TCCRnA`, `TCCRnB`, `OCRnx`, `TCNTn`, `TIMSKn`, etc. | Configure and operate hardware **timers**, generate PWM, measure time, count pulses, generate interrupts, etc. |

### **Control Registers - DDRx, PORTx, PINx** 
Each of these is **8 bits wide**, meaning it controls **8 pins** (even if not all 8 are used)
### **DDRx**
Every I/O **port** (PORTB, PORTC, PORTD) on the ATmega328P has a special register called **DDRx** (Data Direction Register).
Each **bit in DDRx controls one pin** of that port:
- If a bit in `DDRx` is **set to 1**, that pin becomes an **output pin**.
- If a bit in `DDRx` is **set to 0**, that pin becomes an **input pin**.
for example,
- Making Pin D9 (PB1) as output:
  DDRB |= (1 << PB1);
  This sets bit 1 of DDRB to 1
- Making Pin D9 (PB1) as input:
  DDRB &= ~(1 << PB1);
  This sets bit 1 of DDRB to 1

### **PORTx

Every I/O **port** (PORTB, PORTC, PORTD) on the ATmega328P has a special register called **PORTx** (Port Data Register).
Each **bit in PORTx controls the output level (HIGH or LOW)** for one pin on that port:
- If a pin has already been **set as output** using `DDRx`, then:
    - Setting a bit in `PORTx` to **1** makes the pin output **HIGH** (5V).
    - Setting it to **0** makes the pin output **LOW** (0V).
For example:
- To set **Pin D9 (PB1)** HIGH:  
  PORTB |= (1 << PB1);
- To set **Pin D9 (PB1)** LOW:
  PORTB &= ~(1 << PB1);

### **PINx
Every port (PORTB, PORTC, PORTD) has a corresponding PINx register (Pin Input Register) used for reading the current digital state of input pins.
Each bit in PINx tells whether that pin is currently HIGH or LOW:
- If the bit in `PINx` is **1**, the pin is HIGH (receiving 5V).
- If it’s **0**, the pin is LOW (receiving 0V).
For example:
- To read **Pin D4 (PD4)**:
  bool state = PIND & (1 << PD4);
  This checks bit 4 of PIND. If it’s set, the pin is HIGH.

|Register|What it controls|Works on which direction?|
|---|---|---|
|`DDRx[n]`|Sets direction: `1 = output`, `0 = input`|Direction setting|
|`PORTx[n]`|If output → sends `HIGH` or `LOW` to pin If input → enables pull-up resistor|Output/write|
|`PINx[n]`|Reads the digital state of the pin|Input/read|
Example Program:
To **make Arduino Pin 10 an output** and then **turn it ON (HIGH)** and **OFF (LOW)** repeatedly using ***Port Manipulation***.
In the ATmega328P chip inside your Arduino UNO:
- Arduino **Pin 10** is **PB2** — the **2nd bit of PORTB**.
- So we work with **`DDRB`** (to set pin mode) and **`PORTB`** (to write HIGH or LOW).

void setup() {
  DDRB = 0b00000100;
}
void loop() {
  PORTB = 0b00000100;
  PORTB = 0b00000000;
  delay(1000);
}

### **Macros**
They are **shortcuts** that let you quickly **control all pins** in a port (like PORTB, PORTC, PORTD) by **directly writing to hardware registers** without using `pinMode()` or `digitalWrite()`.
Each **port** is like a group of 8 pins. The ATmega328P groups pins into `PORTB`, `PORTC`, and `PORTD`. Each group has a corresponding control register.
### **Timer/Counter Registers**

| Timer      | Bits   | PWM Pins Used |
| ---------- | ------ | ------------- |
| **Timer0** | 8-bit  | D5, D6        |
| **Timer1** | 16-bit | D9, D10       |
| **Timer2** | 8-bit  | D3, D11       |
Each timer has a set of **dedicated registers**, like:

|Timer|Registers|
|---|---|
|Timer0|`TCCR0A`, `TCCR0B`, `OCR0A`, `OCR0B`, `TCNT0`, `TIMSK0`|
|Timer1|`TCCR1A`, `TCCR1B`, `OCR1A`, `OCR1B`, `TCNT1`, `TIMSK1`|
|Timer2|`TCCR2A`, `TCCR2B`, `OCR2A`, `OCR2B`, `TCNT2`, `TIMSK2`|
Common Timer Registers:

| Register                                           | Purpose                                                      |
| -------------------------------------------------- | ------------------------------------------------------------ |
| `TCCRnA/B`<br>**Timer/Counter Control Registers**. | Timer Control: sets PWM mode, compare behavior, clock source |
| `OCRnx`<br>Output Compare Registers                | Output Compare: sets duty cycle for PWM                      |
| `TCNTn`<br>Timer/Counter Register                  | Timer Counter: current timer value                           |
| `TIMSKn`<br>Timer Interrupt Mask Register          | Interrupt Mask: enables timer interrupts                     |


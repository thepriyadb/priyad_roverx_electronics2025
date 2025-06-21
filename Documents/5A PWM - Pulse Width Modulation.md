
## **Pulse Width Modulation (PWM)**

Pulse Width Modulation (PWM) is a digital modulation technique wherein the duty cycle of a fixed-frequency square wave is varied to control the average voltage or power delivered to a load. PWM allows for efficient and fine-grained control of actuators, power converters, LEDs, and motors using digital signals.

### **Principle of Operation**

A PWM signal alternates between HIGH (Vmax) and LOW (0 V) states within a fixed period (T). The ON-time (Ton) is modulated, while the total period (T) remains constant.
The effective (average) voltage seen by the load is given by:
V_avg = Duty_Cycle * V_max

### **Parameters**

| Parameter       | **Symbol** | **Definition**                                                                 |
| --------------- | ---------- | ------------------------------------------------------------------------------ |
| Duty Cycle      | D (%)      | Fraction of the period signal is HIGH<br>Duty_cycle = (T_on/T) × 100%          |
| Frequency       | f (Hz)     | Number of PWM cycles per second<br>f = 1/T                                     |
| Resolution      | R (bits)   | Granularity of duty cycle control<br>8-bit = 256 steps<br>16-bit = 65536 steps |
| Period          | T (s)      | Duration of one full HIGH + LOW cycle                                          |
| Amplitude       | V_max (V)  | Maximum output level during the HIGH phase                                     |
| Average Voltage | V_avg (V)  | Time-averaged output voltage = Vmax * Duty_cycle                               |

### **Arduino PWM Implementation**

| **Timer** | **PWM Pins** | **Bit Width** | **Max Count** | **Remarks**                                  |
| --------- | ------------ | ------------- | ------------- | -------------------------------------------- |
| Timer0    | 5, 6         | 8-bit         | 255           | Used for core timing (`millis()`, `delay()`) |
| Timer1    | 9, 10        | 16-bit        | 65535         | Ideal for precision control, servo PWM       |
| Timer2    | 3, 11        | 8-bit         | 255           | Used in `tone()` and extra PWM channels      |
### **Use Cases**

| **Domain**            | **Application**                                            |
| --------------------- | ---------------------------------------------------------- |
| Motor Drives          | Speed and torque control (via Vavg) in BLDC, DC, AC motors |
| Embedded Systems      | Dimming LEDs, controlling servos                           |
| Communication Systems | Pulse-based modulation techniques                          |

**References:**
https://www.youtube.com/watch?v=B_Ysdv1xRbA
https://www.youtube.com/watch?v=GQLED3gmONg
https://www.youtube.com/watch?v=nXFoVSN3u-E
https://www.youtube.com/watch?v=YfV-vYT3yfQ

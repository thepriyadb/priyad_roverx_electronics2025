# 7A Design a schematic with a fan, an LED and Arduino using KiCAD.md

### Components:
- Fan M2 - 12V DC - Load to be controlled
- Resistor - Limits Gate current
- LED D1 - Visual indicator
- Flyback diode D2 - Protects MOSFET from voltage spikes when fan turns OFF
- N-Channel MOSFET - Acts as a digital switch
- Arduino Uno R3
- PWR_FLAG - used in KiCAD to recognise external power sources in ERC

![7-Fan+LED.png](.../Documents/Images/7-Fan+LED.png)

### Working:
Controlling FAN using N-Channel MOSFET
MOSFET connects fan's -ve terminal to GND.
When Arduino outputs 5V on pin 9, the Gate Voltage is greater than source Voltage (0V) which turns ON the MOSFET. The current flows from 12V source to fan then drain and source and to GND again. Then the FAN starts running.
When Arduino outputs LOW 0V, the gate voltage = source voltage = 0V, turning the MOSFET off. Then FAN stops.

### Protection from Flyback diode
Fan is an inductive load. When switching OFF, they generate a reverse voltage spike called back MEF. The IN4007 diode D2 conducts and dissipates the spike safely across the fan instead of damaging the MOSFET.

### LED Indicator

### Why N-Channel MOSFETinstead of P-Channel MOSFET?
Simpler low-side siwtching

### Why MOSFET and not BJT? 
Faster switching
MOSFET is voltage controller so power loss is less
Higher speed -> better PWM control

### Why use a GATE resistor?
Limits inrush current and protects Arduino pin



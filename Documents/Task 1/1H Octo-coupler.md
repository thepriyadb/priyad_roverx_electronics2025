
## **Optocoupler**

References: https://www.nutsvolts.com/magazine/article/optocoupler-circuits
An optocoupler, also known as an optoisolator or photocoupler, is an electronic device made up of an LED emitter combined with a photodetector, separated from each other in proximity.

**Uses**
Optocouplers manage to send signals between circuits with separate grounds, providing an isolated galvanic barrier between them. Therefore, an optocoupler is a solution for circuits that need to be isolated from each other for safety or regularity reasons and need to have interaction in between.
1. **Preventing Ground Loops in Remote Equipment:**  
Sometimes, electronic equipment in one place needs to control something far away. If both devices are connected directly through wires, it can create unwanted loops in the electrical ground path. This can cause noise, errors, or even damage. Optocouplers help by keeping the control and power sides completely separate. They pass signals using light instead of direct wires, so there’s no electrical connection — just clean, safe control. That’s why they’re widely used in power supplies for computers and communication devices.
2. **Reducing Electrical Noise:**  
Digital circuits (like microcontrollers or computers) can create electrical noise which means little bursts of unwanted signals. If this noise gets into the part of your circuit that measures things, like a sensitive sensor or ADC (Analog-to-Digital Converter), it can ruin the accuracy. Optocouplers act like a noise-blocking wall between the digital and measuring parts. They send the signal through light, which doesn’t carry that unwanted noise, keeping your readings clean and accurate.
3. **Safely Sending Signals to High-Voltage Circuits:**  
In some electronic designs, you need to send a signal to a part of the system that’s working at a very high voltage. Connecting to it directly would be dangerous. Instead, optocouplers send the signal using light, without any direct contact. This way, you can control high-voltage circuits safely from a low-voltage side, which is especially useful in power supply designs and electric motor control.

---
## Structure

![[Pasted image 20250529135257.png]]

An optocoupler is made up of two electrically isolated circuits. The first circuit has an infrared emitting diode, whereas the second circuit contains an infrared sensor device, such as a photodiode, phototransistor, photo TRAIC, or photo SCR. Glass, air, or translucent plastic can be used to fill the space between the two circuits. The light is emitted by the LED, and it is received and amplified by the phototransistor. The anode and cathode of the LED are the first and second pins, whereas the emitter and collector of the phototransistor are the third and fourth pins.

---
## Working:

![[Pasted image 20250529134832.png]]

First, the current is applied to the optocoupler, which causes the LED to generate infrared light proportional to the current flowing through it. When light strikes the photosensor, it conducts a current and turns on. The IR beam is switched off when the current running through the LED is disrupted, forcing the photosensor to stop conducting. The photosensor is the output circuit that detects light, and the output is either AC or DC depending on the type of output circuit.
The output of an electrically isolated circuit is controlled by adjusting the circuit’s input, which is the basic operating concept of an optocoupler. A voltage source provides input to the Infrared LED, and the intensity of the voltage source can be varied by altering the input voltage. The light emitted has a specific wavelength. This light is detected by the photodetector, which turns light energy into photocurrent. The generated output current is then amplified. The output current is proportional to the amount of light that strikes the device.

---
## Configurations

In DC circuits, **photo-transistor** and **photo-Darlington** are commonly utilized, whereas **photo-SCR** and **photo-TRIAC** are commonly employed to control AC circuits.

![[OctocouplerConfigurations.png]]

---
## **Digital interfacing**

Optocoupler devices are ideally suited for use in digital interfacing applications in which the input and output circuits are driven by different power supplies. They can be used to interface digital ICs of the same family (TTL, CMOS, etc.) or digital ICs of different families, or to interface the digital outputs of home computers, etc., to motors, relays, and lamps, etc. This interfacing can be achieved using various special-purpose ‘digital interfacing’ optocoupler devices, or by using standard optocouplers.

**TTL Interface**

![[TTLInterface.png]]

The circuit in this figure is used to safely connect two digital (TTL) circuits using a device called an optocoupler. An optocoupler sends signals using light instead of direct wires, which protects the two circuits from damaging each other.
In this setup, the first TTL circuit controls an LED (inside the optocoupler). But *TTL outputs are better at pulling signals down to 0 volts than pushing them up to 5 volts*. That’s why the LED is connected between 5V and the output pin of the first TTL chip. This way, when the output goes LOW, it allows current to flow through the LED, turning it ON. When the output goes HIGH, the LED should turn OFF.
However, there's a problem: TTL outputs sometimes don’t go all the way up to 5V—they might stop at around 2.4V, which might not be enough to fully turn the LED off. To fix this, a pull-up resistor is added to help pull the voltage up to 5V properly so the LED fully turns off when needed.
On the other side of the optocoupler is a phototransistor. When the LED is ON, light turns on this transistor, which pulls the second TTL input LOW—this tells the second circuit it’s getting a "0". When the LED is OFF, the transistor is OFF, and the input stays HIGH—meaning it's a "1". This setup cleanly passes the signal from one circuit to another without direct contact and keeps the logic (0 or 1) the same.

**CMOS Interface**

![[CMOS.png]]

CMOS ICs (another type of digital chip) are better than TTL in one big way: they can both pull the signal up and down equally well. This means they can push current out (source) and pull current in (sink) with similar strength, usually a few milliamps.
Because of this, you have two choices when using a CMOS chip to control an optocoupler:
1. Sink configuration (like in TTL Interface): The LED is between the 5V line and the CMOS output, so the CMOS chip pulls current down through the LED when it goes LOW.
2. Source configuration (like in CMOS Interface): The LED is between the CMOS output and ground, so the CMOS chip pushes current up through the LED when it goes HIGH.
Both methods work well with CMOS because it’s strong in both directions. But in either setup, there’s a resistor (called R2) in series with the LED. This resistor’s job is to control the current and make sure the voltage at the output moves all the way between logic-0 and logic-1 (usually 0V and 5V). If the resistor is too small, the voltage might not swing fully, which could cause incorrect operation. So, R2 needs to be large enough to keep things working properly.

---
## **Analog Interfacing**

![[AudioCouplingCircuit.png]]

An optocoupler can also be used to transfer analog signals, like audio, from one circuit to another while keeping them electrically isolated. Figure 17 shows how this is done using an op-amp and an optocoupler.

In this circuit, the op-amp is set up as a voltage follower—this means it copies the voltage you give it at the input (pin 3) to the output. The special part is that the LED inside the optocoupler is placed in the feedback path of the op-amp. This makes the current through the LED follow the input voltage exactly. The input is biased (set) at half the supply voltage using two resistors (R1 and R2), so the signal can swing up and down around this middle point. An audio signal is added on top of this bias using a capacitor (C1), which blocks DC and lets the changing (AC) part of the signal through. The resistor R3 sets a steady (quiescent) current of 1–2 mA through the LED when there's no audio signal.

On the output side of the optocoupler, the phototransistor responds to the light from the LED. It creates a small current that flows through RV1, a variable resistor (potentiometer). This sets a steady voltage (quiescent voltage) across RV1. You adjust RV1 so that this voltage sits at about half the supply, just like the input. As the LED current changes with the audio signal, the phototransistor current also changes, creating a matching audio signal across RV1. Finally, a capacitor (C2) removes the DC part of the signal, so only the clean audio comes out.

---
## **Triac Interfacing**

![[Triac.png]]

A great use of an **optocoupler** is to connect a **low-voltage control circuit** (like from a microcontroller or switch) to a **high-voltage AC circuit** that controls things like **lamps, heaters, or motors**. This keeps the low-voltage side safe from the dangerous high-voltage side.
Figure 18 shows a circuit that does this using a **triac** (a device that switches AC power). It uses an **optocoupler** to safely turn the triac **on or off**.
Here’s how it works:
- The circuit makes its own **10V DC supply** from the AC mains using components like **R2, D1, ZD1, and C1**.
- This 10V is used to control the triac through a transistor **Q1**.
- When the switch **SW1 is open**, the optocoupler is OFF, Q1 is OFF, and the triac does nothing—so the **load (lamp, heater, etc.) stays OFF**.
- When **SW1 is closed**, the optocoupler turns ON, which turns **Q1 ON**, sending the 10V to the **triac gate** through resistor R3. This turns the **triac ON**, allowing **AC power to flow** to the load.
Note: This is a **non-synchronous** switch, meaning the triac turns on at any point in the AC wave, not just at zero voltage crossing.

---
## Applications

Optocouplers can either be used on their own as a switching device or with other electronic devices to provide isolation between low and high-voltage circuits. You’ll typically find these devices being used for: 

- Microprocessor input/output switching
- DC and AC power control
- Communications equipment protection
- Power supply regulation

---

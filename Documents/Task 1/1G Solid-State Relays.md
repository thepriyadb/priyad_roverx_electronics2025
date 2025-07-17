## **Solid-state Relays**

References:
https://www.youtube.com/watch?v=fV2xfSWcVZg
https://www.build-electronic-circuits.com/solid-state-relay-ssr/
https://www.ia.omron.com/support/guide/18/introduction.html

A Solid-state relay (SSR) is an electronic switch without moving parts that use semiconductor technology to turn things on and off.

---
## Working: 

To understand how SSRs work, take a look at following diagram that shows what an SSR looks like on the inside:

![Inside of an SSR](https://www.build-electronic-circuits.com/wp-content/uploads/2024/05/Inside_relay.png)

The SSR has three main components:
- A Light-emitting device
- A light sensor (ex a photodiode)
- A switching device (ex a transistor)
When a control signal (e.g., 5V DC) is applied to the input terminals of the SSR, it powers the LED. When the LED turns on, the light is detected by the light sensor on the output side and turns on the switching device so that current can flow.
This isolates (electrically) the low-voltage control side from the high-voltage load side. Such a setup is called an _optocoupler_.
The light sensor activates the trigger circuit, turning on the switching device in the output circuit, thereby connecting the power source to the load. The switching device remains on as long as the control signal is present, keeping the load powered. When the control signal is removed, the LED turns off, the light sensor stops detecting light, the trigger circuit deactivates the switching device, and the load is disconnected from the power source.
The switching device can be a MOSFET transistor, an IGBT, a Triac, or an SCR, depending on the type of SSR you are working with.

Step 1: Control signal is sent to input side
The operation of a Solid State Relay begins when a **control signal**, typically a low-voltage DC (such as 5V or 12V), is applied to the input terminals of the SSR. In some models, AC control signals are also supported. This signal usually comes from a digital controller like an Arduino, PLC, or microprocessor. The purpose of this signal is not to power the load directly, but simply to "tell" the SSR when to switch on or off.
In SSRs little current is required at the control input. The current needed is typically in the range of a few milliamperes which is enough to power a small internal LED in the optocoupler. This makes SSRs compatible with low-power control systems while still being capable of switching heavy loads on the output side.
SSRs rely on a non-contact method of switching. This means that once the signal is applied, there are no clicks or movements, and the switching happens silently and nearly instantaneously.
The input side is typically designed to accept a specific voltage range. Applying a voltage within this range activates the next stage in the relay, the **opto-coupler**.

Step 2: Opto-coupler activates the semiconductor switch
Once the control signal reaches the SSR, it powers a LED inside an opto-coupler. The opto-coupler is a critical safety and performance component. The LED emits infrared light, which travels a tiny gap within the component and strikes a light-sensitive semiconductor like a phototransistor on the other side.
This optical transmission serves two major purposes:
1. Electrical Isolation ensures that the low voltage control circuit is completely isolated from the high-voltage power circuit, preventing any backflow of current or dangerous voltage spikes.
2. Signal Transfer: The light from the LED “commands” the switching element on the output side to conduct electricity.
Once activated by the light, the phototransistor sends a small signal to trigger the power semiconductor switch such as a triac, thyristor, MOSFET, or transistor. The choice of semiconductor depends on whether the SSR is for AC or DC applications.
This triggering step takes just microseconds. allowing SSRs to switch much more quickly than mechanical relays. There's no physical wear and tear, so the relay can be used for millions of switching cycles with consistent performance.

Step 3: Load circuit closes and current flows
Now that the power semiconductor is triggered, the SSR completes the circuit on the output side. This implies the "switch" is now ON, and current is allowed to flow through the load which could be a lamp, heater, motor, solenoid, or other device.
For DC loads, the semiconductor (like a MOSFET or BJT) acts as a unidirectional switch. When it's turned on, it allows current to pass from the positive terminal to the negative terminal, just like a traditional transistor switch.
For AC loads, things get slightly more complex. Here, triacs or back-to-back SCRs (thyristors) are used. These components can handle the alternating nature of AC current which means they can conduct during both the positive and negative halves of the AC sine wave. Once turned on, they will continue conducting until the current naturally drops to zero at the end of each half-cycle.
The result is a completely closed circuit on the output side, with electrical current flowing efficiently and silently. During this stage, no mechanical contact is made, which means there is no arcing, sparking, or noise. This makes SSRs ideal for use in environments where reliability and quiet operation are essential.

Step 4: Zero-cross switching in AC SSRs
In alternating current (AC) systems, the voltage constantly swings between positive and negative values in a smooth, wave-like pattern called a sine wave. During every cycle of this waveform, the voltage reaches zero volts twice, once when transitioning from positive to negative, and once when going from negative to positive. These moments are called "zero-crossings".
Now you want to turn ON an AC-powered load like a lamp or a heater. If you close the circuit at the peak of the voltage (like 230V), the sudden surge of current can be harsh and damaging, especially for sensitive or inductive loads like motors. This sudden inrush can:
- Generate high electrical noise (EMI),
- Stress the internal components of the SSR and load,
- And shorten the lifespan of the devices involved.
To solve this problem, many AC SSRs include a zero-cross detection circuit that ensures switching occurs only when the AC voltage is at or near 0V which is a very calm, low-energy moment in the cycle. This is called zero-cross switching.

---
## Types:

Classification depends on the **type of input signal you can apply and the type of load you can control**.
- DC-to-AC
- AC-to-AC
- DC-to-DC
- DC and AC output
### DC-to-DC SSR
A DC-to-DC SSR would allow you to use a low-voltage DC signal to control another DC device. These relays typically use switching devices like MOSFETs or IGBTs transistors at the output to control the flow of current in the DC circuit. Take a look at its circuit:

![DC-to-DC Solid state relay](https://www.build-electronic-circuits.com/wp-content/uploads/2024/05/DC_DC.png)

### DC-to-AC SSR
With this kind of SSR you can use a low-voltage DC signal to control a device that runs on AC power. A DC-to-AC SSR relay typically has a Triac or SCR (Silicon Controlled Rectifier) at the output. These components are used to switch the AC load on or off when they receive the signal from the control circuit. You can check its internal diagram below:

![DC-to-AC Solid state relay](https://www.build-electronic-circuits.com/wp-content/uploads/2024/05/DC_AC_.png)
   
### AC-to-AC SSR
The AC-to-AC SSR, along with the components previously mentioned, such as the led, the light sensor and the Triac or SCR at the output, there’s a rectifier bridge in the input circuit. This rectifier bridge is responsible for converting the AC control signal into a form that can be used to activate the relay and control the AC load.

![AC-to-AC Solid state relay](https://www.build-electronic-circuits.com/wp-content/uploads/2024/05/AC_AC.png)

### DC and AC Output SSR
These relays are useful when you need to control both DC and AC devices or circuits using the same control signal. They typically incorporate different types of switching components for DC and AC output, such as MOSFETs or IGBTs for DC and Triacs or SCRs for AC.

![DC and AC output Solid state relay](https://www.build-electronic-circuits.com/wp-content/uploads/2024/05/AC_AND_DC-1024x442.png)

---
## Types of SSR Configuration

Various SSR packaging/integration styles:

**Integrated with Heat Sink**  
→ Heat sink pre-attached by manufacturer  
→ Ready for high current & continuous load  
→ Easy to install, no extra cooling needed  
→ Used in industrial & heavy-duty applications
The integrated heat sink enables a slim design. These relays are mainly installed in control panels.

![[relay1.png]]

**Separate Heat Sink**  
→ Heat sink sold separately  
→ User attaches suitable heat sink based on load  
→ Flexible for different power and space needs  
→ Common in customizable industrial setups
Separate installation of heat sinks allows the customers to select heat sinks to match the  
housings of the devices they use. These relays are mainly built into the devices.

![[Pasted image 20250529130816.png]]

**Relay-Shaped SSR (Mechanical Lookalike)**  
→ Same size and pin layout as mechanical relays  
→ Easy drop-in replacement in existing systems  
→ Fits relay sockets or DIN rails  
→ Offers silent, maintenance-free switching
These relays have the same shape as plug-in relays and the same sockets can be used. They are usually built into control panels and used for I/O applications for programmable controllers and other devices.

![[Pasted image 20250529130928.png]]

**PCB-Mounted SSR**  
→ Compact size for soldering directly on PCB  
→ Lower power rating than panel-mount SSRs  
→ Ideal for embedded systems and small circuits  
→ Saves space and simplifies assembly

![[Pasted image 20250529131023.png]]


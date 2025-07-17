
---
## **Relays** 

Relay is an electrically operated switch activated by an electromagnet which pulls a set of contacts to make or break a circuit. It uses a small electrical signal to control a large electrical circuit. They use them to turn on/off high-power devices like lamps or garage door motors with just a small DC voltage signal.

---
**Construction**:

![Relay diagram](Relay.png)

A basic electromechanical relay is constructed using an electromagnet, a movable armature, and a set of contacts. The electromagnet, made of a coil and an iron core, creates a magnetic field when energized. This field pulls the armature, which in turn activates or deactivates the contacts, controlling a circuit.

**Inside the relay:**

![Inside relay digram](InsideRelay.png)

The _coil_ pins control the switch, and the _NC_, _NO_, and _COM_ pins make up the switch.

![Inside relay](InsideRelay2.png)

A coil wound around a magnetic core makes up an electromagnet. It generates a magnetic field around it when an electrical current passes through the coil.
The armature is a movable component within the relay. When the coil is energized, the magnetic field it produces attracts the armature, causing it to move.
The return spring is connected to the armature, providing a restoring force when the coil is de-energized. It ensures that the armature returns to its original position when the electrical current through the coil ceases.
Attached to the armature through the return spring, the moving contact physically moves with the armature. When the armature is attracted by the energized coil, the moving contact changes its position, either making or breaking contact with the fixed contacts.
- Fixed Contact – Normally Closed (NC): The NC contact is closed (connected to COM) when the relay is not energized.
- Fixed Contact – Normally Open (NO): The NO contact is open (disconnected from COM) when the relay is not energized.
- In a relay, the "COM" (Common) pin serves as a shared connection point for the Normally Open (NO) and Normally Closed (NC) contacts. When the relay is deactivated, the COM pin is connected to the NC contact, and when the relay is activated, the COM pin switches to connect with the NO contact.

---
**Single Phase SSR:**
A single phase SSR is an electronic switching device used to control AC/DC loads in single phase systems without any moving parts. It uses semiconductor components like triacs (for AC) or MOSFETs (for DC), triggered by a low voltage DC control signal through an optocoupler, which ensures electrical isolation between the control and power sides. These relays are commonly used in applications like electric heaters, LED lighting, fans, and small automation circuits due to their fast response, silent operation, and long lifespan. They often include zero-cross switching for AC loads to minimize electrical noise and component stress. However, they typically require heat sinks to manage heat dissipation during prolonged or high-current operation.

**Three Phase SSR**
A three-phase SSR is designed to control high power three phase AC loads by simultaneously switching all three phases (L1, L2, L3) using internal semiconductor components such triacs. Triggered by a low voltage control signal and isolated via optocouplers, these relays are ideal for industrial applications like motors, pumps, HVAC systems, and machinery that operate at higher voltages (400–480V). They provide noise free, fast, and maintenance free operation with superior resistance to mechanical wear, vibration, and arc damage. Due to the high currents involved, proper heat dissipation through large heat sinks or fan-cooled systems is crucial to ensure safe and reliable operation over time.

---
## Pin Connections:

Normally Open (NO) Pin Connection:
If you want the device that you want to switch on/off to be disconnected from power when the relay is not activated, you need to use the normally open (NO) pin. As soon as the relay coil receives power, the switch closes, completing the circuit and allowing electricity to flow through it so that whatever you’ve connected turns on.

![[NormallyOpen.png]]

Normally Closed (NC) Pin Connection:
If you want the device that you want to control to be connected to power when the relay is not activated, you need to use the normally closed (NC) pin. As soon as the relay coil receives power, it causes the switch to open, interrupting the circuit and stopping the flow of electricity to your device.

![[NormallyClosed.png]]

## Relay Switch types:

* SPDT Relay: Single Pole Double Throw (SPDT). It’s the most commonly used. It’s a 5-pin relay with the following pins:
  The _COM_ pin is always used. And although you can use both _NC_ and _NO_, it’s common to use just one of them.
  
  ![[SPDT.png]]
  
* Single Pole Single Throw (SPST) : This relay has one normally open (NO) and one common (COM) contact. It can either connect or disconnect a single circuit.
  
  ![SPST Relay symbol](https://www.build-electronic-circuits.com/wp-content/uploads/2024/02/Relay-_SPST.png)

* Double Pole Single Throw (DPST) : DPST relays feature two sets of contacts, each set capable of controlling a single circuit. Both switches can be open or closed simultaneously.
  
  ![DPST Relay symbol](https://www.build-electronic-circuits.com/wp-content/uploads/2024/02/Relay-_DPST.png)

  * Double Pole Double Throw (DPDT) : DPDT relays have two sets of contacts, each set capable of controlling two separate circuits. It provides a double-throw functionality for each of the two poles.
  
  ![DPDT Relay symbol](https://www.build-electronic-circuits.com/wp-content/uploads/2024/02/Relay-_DPDT.png)
## Types of Relays:

1) **Latching Relay**: 
   Latching relays are commonly used in low power consumption or high temperature applications where applying coil power for a long time cannot be afforded due to power consumption or self heating of the coil. Instead of a continuous voltage applied to the coil, they are operated with short voltage pulses instead. Latching relays change contact position when a coil voltage is applied and remain in that position even if the voltage is disconnected. 
   They are characterized by their bistable operation, meaning they have two stable positions: set (on) and reset (off).
   A latching relay maintains its most recent state or position even when the signal that activated it is no longer present. It can stay in the 'on' or 'off' state without a constant power supply. Once triggered, its position is 'latched' into place. The latching relay can be operated manually, remotely, by impulses, or using different control inputs.

   **Working:**
   The operational mechanism of a latching relay is fundamentally similar to that of a conventional relay, with the key difference being that it does not require a continuous power supply to remain in an energized state. Current pulses are utilized to activate (trigger) and deactivate (reset) the relay, facilitating its transition between states or positions.
   
   **Types:**
   * **Single coil and dual coil:** These are the most common type, using electromagnetism to hold the contacts in their position. Single coil type requires a pulse of current in one direction to activate and another in the opposite direction to reset. Dual coil type controls one state (activation or reset), independent of polarity.
   * **Magnetic:** Magnetic latching relays use permanent magnets to maintain their position after being actuated. They can be either single or dual-coil operated. The permanent magnet holds the armature in the last position it was moved to by the coil.
   * **Mechanical:** Mechanical latching relays use a ratchet and pawl mechanism to maintain the position of the contacts. The relay is set or reset by moving the pawl with a pulse to the coil.
   * **Electronic (solid-state relays):** These are not traditional electromechanical relays but use semiconductor devices to perform the latching function without moving parts. They maintain their state using electronic circuitry rather than a mechanical mechanism.
   **Applications:** Utility meters, portable medical devices, security systems.

2) **Reed Relay:** A reed relay is a small electromagnetic switching device. Reed relays are made by placing a coil around one or more reed switches. A reed switch uses simple magnetic interaction to open and close it's contacts. And they consume in their normally open state.
   
   ![[ReedRelays.png]]
   
   There are four contact forms, Form A, B, C, and E.
   First, is the Form A type which is the most common and rests in a normally open (N.O.) switch state. **Form A relays** remain OPEN or OFF until current passes through the coil. The electromagnetic coil produces a magnetic field equal to a permanent magnet. Finally, the resulting magnetic field closes the contacts, switching the relay ON. Conversely, when the coil current is removed, the switch turns off and the contacts return to their open state.
   Next is our second type Form B relays which have normally closed (N.C.) biased contacts held by a magnet. So, the relay rests in the closed or off state until the coil is energized, opening the contacts. De-energizing the coil switches the relay back to its closed or off position.
   Third, is the **Form C** **relay** which is uniquely comprised of three contacts compared to the typical two. They are normally open, normally closed, and common. The common contact will swing from the closed contact to the open contact when switched on. When OFF the contact reverts to its resting closed state. Therefore, Form C types are also referred to as a double throw switch.
   The fourth and final type **Form E** is what we call a latching or bistable relay. This relay can exist in either the N.O. or N.C. state with no coil power using a biasing magnet. The relays’ contacts maintain their last assumed position without activating the coil. To change the state of the contacts, the magnetic field must be reversed.
   **Applications:** Hybrid & Electric Vehicles
   
3) **Polarized relay :** Polarized relays have contacts that are polarized to ensure proper operation in DC circuits. They are designed to prevent reverse polarity issues.
   
4) **High-Frequency Relay:** These relays are designed to operate reliably at high frequencies, making them suitable for applications where the cycle of on/off occurs in short periods.

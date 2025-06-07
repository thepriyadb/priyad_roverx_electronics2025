## **CAN**

References:
https://www.youtube.com/watch?v=JZSCzRT9TTo
https://www.youtube.com/watch?v=VClOpxJcmTU&list=PLERTijJOmYrApVZqiI6gtA8hr1_6QS-cs&index=6

CAN (Controller Area Network) is a communication protocol designed for robust and fast data exchange between electronic devices (ECUs) inside vehicles and other systems like robotics.
- It’s fast and reliable, perfect for safety critical systems in cars, electric vehicles, and industrial machines.
- It connects many ECUs (Electronic Control Units) small computers controlling everything from motors to brakes to windows so they can talk to each other.
CAN uses a *shared bus topology*, meaning many devices (nodes) connect to the same *two-wire bus*, no master device controlling everything. The two wires are called *CAN High* and *CAN Low*, and they’re *twisted together* to reduce EMI. The signal on the bus is the difference in voltage between CAN High and CAN Low, this *differential signaling* makes the communication very noise resistant. At each end of the bus are *terminating resistors* (usually 120 ohms) to prevent signal reflections that cause errors.

**How Do Nodes Avoid Talking Over Each Other?**

When multiple ECUs want to send data simultaneously, CAN uses a clever system called *arbitration*:
- Every node has a unique *ID* number.
- When two or more nodes start sending at the same time, they send their ID bits bit-by-bit.
- In CAN, a *0* bit is *dominant* over a 1 bit, so if one node sends a 0 while another sends a 1, the one sending the 1 must stop transmitting => it lost arbitration.
- This means the node with the lowest ID (highest priority) wins and gets to send its message first.
- Nodes detect whether they’ve won by reading back what they sent and comparing it to the bus state. If the bit sent and the bit on the bus are the same, the node continues transmitting. If the bit sent is recessive bit (logic 1) but the bus shows a dominant bit (logic 0), it means another node with a higher priority message is transmitting. When this mismatch happens, the node knows it has lost arbitration and stops transmitting.
  **![BitArbitration](https://lh7-rt.googleusercontent.com/docsz/AD_4nXeRI1XFXIgd0Xa8A2nix7o3qU35piOxFMQDB0EHcc_8TWUoor77Ap7A8oFpbN2OphvuFIaD2awNtKUr_T9SOt5UQwzCfPw51OewxvraphIZLuUh4k9X-ii3JhiVvi9RWX2yTxxxuQ?key=jE-ynQ9rlYMhfBxFsbcH2w)**

## Communication Sequence

The CAN communication process begins when the bus is in an *Idle State*, where both *CAN High* and *CAN Low* lines remain at a *recessive* voltage level (logic 1). This indicates that no communication is taking place and the bus is free for any node to initiate a transmission.

![[CANComm.png]]

![[CANComm2.png]]

When a node wants to transmit data, it signals the Start of Frame by driving a dominant bit (logical 0) onto the bus. This transition marks the beginning of a message and alerts all other nodes to monitor the transmission.

![[CANsof.png]]

Following this, the bus enters the Arbitration Phase, which ensures that only one node transmits at a time. Each node transmits its message ID bit-by-bit while simultaneously monitoring the bus. Due to the dominant bit having priority over the recessive bit, the node with the lowest numerical ID continues transmitting, while others detect a mismatch and immediately stop, deferring their transmission. This mechanism guarantees non-destructive priority-based access.

![[CANbitbybit.png]]

![[CANnode2recessive.png]]

Once arbitration is complete, the winning node sends the Control Field, which includes important information such as the Data Length Code (DLC) indicating how many bytes of data will follow. This is crucial for all listening nodes to know how much data to expect.

The Data Field comes next and contains the actual payload, typically up to 8 bytes in classical CAN and up to 64 bytes in CAN FD (Flexible Data rate). This field carries the information relevant to the operation of the system, such as sensor values, actuator commands, or status updates.

To ensure data integrity, the CRC Field (Cyclic Redundancy Check) is included. This field allows all receivers to verify whether the message was received without errors. The sender calculates a CRC value based on the message, and receivers compare it to their own calculation of the CRC.

After the CRC check, the ACK Field is transmitted. All receivers who correctly received the message will drive a dominant bit in this field to acknowledge receipt. The transmitter checks this bit to confirm successful delivery. If no acknowledgment is received, the transmitter assumes an error occurred and may attempt retransmission.

Finally, the message ends with the End of Frame, a sequence of recessive bits indicating that the bus is free again. A short Inter-frame Space follows, acting as a buffer period before any new transmission can begin.

## Main components

![[CANTransciever.png]]
The most fundamental parts include the microcontroller, the CAN controller, and the CAN transceiver.

At the core of the system is the *microcontroller (MCU)*. It runs the application logic, processes sensor inputs, and makes decisions. However, it cannot directly communicate over the CAN bus lines. That’s where the *CAN controller* comes in. It operates *application layer*, meaning it deals with what messages to send or respond to and not how they are sent on the bus. Some examples are STM32, ATMega328P, etc. It acts as the main control unit in an embedded system. It executes the application layer logic such as reading sensor values, sending and receiving data over communication protocols. 
MCU with integrated CAN controller include - STM32
MCU without integrated CAN controller include - ATmega328P - requires external CAN controller such as MCP2515.

The *CAN controller* is responsible for creating and interpreting CAN frames it handles message formatting, arbitration, error detection, and filtering. Many modern microcontrollers include an integrated CAN controller. If not, an external CAN controller (like the MCP2515) can be used. It handles all *Data link layer* functions. It is responsible for bit *timing and synchronization* which ensures proper timing alignment and clock synchronization with other nodes. It ensures a collision free access to the bus by implementing bitwise arbitration. It implements mechanisms like CRC check, ACK check, bit monitoring.

To physically transmit and receive signals over the bus, a *CAN transceiver* is required. 
Signal conversion: 
Transmit (TX) : This translates the digital data from the CAN controller into differential voltage signals suitable for the CAN bus (CAN High and CAN Low). 
Receive (RX) : It also receives those differential signals and converts them back into standard logic levels for the controller to process. 
Commonly used transceiver chips include the **SN65HVD230**, and **MCP2551**. These are critical for ensuring electrical compatibility and signal robustness across the network. It operates at *physical layer*. 

The CAN bus itself consists of a twisted-pair cable, one for CAN_H and one for CAN_L to carry the differential signal. To maintain signal integrity and avoid reflection at the ends of the transmission line, termination resistors (typically 120 ohms) are added at both ends of the bus.
A complete CAN node includes:
- A microcontroller (for application logic),
- A CAN controller (for protocol handling),
- A CAN transceiver (for voltage-level conversion),
- Bus wires (twisted pair for CAN_H and CAN_L),
- And termination resistors (for signal stability).
## Physical Layer = How the signal travels on wires?

The _physical layer_ in a CAN system refers to how data is physically transmitted as electrical signals over wires. 

CAN uses two special wires called _CAN High (CAN_H)_ and _CAN Low (CAN_L)_. These wires carry opposite voltage signals, and the system doesn’t directly interpret 1s and 0s like in regular logic systems. Instead, it uses the _difference in voltage_ between these two wires, a technique called _differential signaling_. This approach is highly reliable because it helps protect against electrical noise and interference that might occur in harsh environments, such as inside a vehicle or factory.

In this system, when there’s a difference of about _2 volts_ between CAN_H and CAN_L (CAN_H around 3.5V and CAN_L around 1.5V), the signal is interpreted as a _dominant bit_ (logic 0). When both lines are at the same voltage (typically 2.5V), the signal is interpreted as a _recessive bit_ (logic 1). Since only the difference matters, even if electrical noise affects both wires equally, the system can still read the correct data. That’s why differential signaling makes CAN _highly noise-resistant_.

The CAN_H and CAN_L wires are also _twisted together_. Twisting ensures that both wires pick up the same amount of noise from the environment, which helps keep the voltage difference unchanged. This further enhances protection from EMI. To keep the signals clean and avoid reflections _termination resistors_ are added at both ends of the bus. These are typically _120-ohm resistors_ placed between CAN_H and CAN_L. They serve two purposes: they _match the cable’s impedance_ to avoid signal distortion, and they _absorb reflections_ that would otherwise interfere with the communication.

Another important component is the _CAN transceiver_. (Refer the section above this).

**![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXcoxUFU7ZpOW44E_nIw0VLDprQQQdiW9S6GjFAbT0yoPRuXI8BP4LvrXAMrE_AEROsUsB5WLAucHyx3ARS7BtsHPthlmiUPvzz1UA8hSlZzzxCXTfaZsX3nirSiP2-nC3WERgIb?key=jE-ynQ9rlYMhfBxFsbcH2w)**

## Data Link Layer = How messages are packed and handled?

The _data link layer_ in a CAN system is responsible for managing how messages are structured, transmitted, and verified across the network. It defines the format of each message frame, which includes fields like the _identifier_ (used for message priority), _data length_, the actual _data payload_, a _CRC_ field for error detection, and an _ACK_ field for acknowledgment by receivers.

This layer also handles access to the bus when multiple nodes want to transmit simultaneously. It uses a method called _arbitration_, where all nodes monitor the bus while sending. If a node detects that another message has a higher priority, based on its _identifier_, it stops transmitting without disrupting the ongoing communication. This ensures that only one message is transmitted at a time, with the highest-priority message winning control of the bus.

The data link layer checks for transmission errors using _cyclic redundancy checks (CRC)_ and ensures reliability through acknowledgment signals. If any errors are detected or acknowledgments are not received, retransmission mechanisms can be triggered.

**![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXdQVJUiKfSsjUduchwxDfGxyZWIuIW8c-NTFSO_UCVlEFlOAhWqnEALc-36OAN9yVXkuSbakiRSvsx_6YuGSXMOdanK9O_NIPfKqpZzUj7mxZK2JwL2lKaFR9qjSs5b3_WdZIHq?key=jE-ynQ9rlYMhfBxFsbcH2w)**

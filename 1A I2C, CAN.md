## **I2C**
I2C is a two-wire serial communication protocol using a serial data line (SDA) and a serial clock line (SCL). The protocol supports multiple target devices on a communication bus and can also support multiple controllers that send and receive commands and data. Communication is sent in byte packets with a unique address for each target device.
I2C is a widely-used protocol for many reasons. The protocol requires only two lines for communications. Like other serial communication protocols, there is a serial data line and a serial clock line. I2C can connect to multiple devices on the bus with only the two lines. The controller device can communicate with any target device through a unique I2C address sent through the serial data line. I2C is simple and economical for device manufacturers to implement.
## I2C Speed Modes
I2C has several speed modes starting with the Standard-mode (Sm), which is a serial protocol that operates up to 100 kilobits per second (kbps). This mode is followed by the Fast-mode (Fm) which tops out at 400 kilobits per second. Fast-mode can be used by the controller if the bus capacitance and drive capability allow for the faster speed. Both of these protocols are widely supported. The Fast-mode Plus (Fm+) mode allows for communication as high as 1 megabit per second (Mbps). To achieve this speed, drivers in the devices require extra strength to comply with faster rise and fall times. These three modes are relatively similar, using a communication structure that is the same. However, all have different timing specifications for each of the modes and hardware implementation of the I2C in the devices are different to accommodate the different speeds. I 2C also has two other modes for higher data rates. High-speed mode (Hs-mode) has a data rate to 3.4 megabits per second. In this mode, the controller device must first use a controller code to allow for high-speed data transfer. This enables high-speed mode in the target device. This mode can also require an active pullup to drive the communication lines at a higher data rate. Ultra-Fast mode (UFm) is the fastest mode of operation and transfers data up to 5Mbps. This mode is write-only and omits some I2C features in the communication protocol.
## I2C Physical Layer

**Two-Wire Communication**
An I2C system features two shared communication lines for all devices on the bus. These two lines are used for bidirectional, half-duplex communication. I2C allows for multiple controllers and multiple target devices. Pullup resistors are required on both of these lines.

Typical I2C Implementation
I²C is a popular communication protocol mainly because it only uses **two lines**:
- **SCL (Serial Clock Line)** – controlled by the master (controller), used to time the data flow.
- **SDA (Serial Data Line)** – carries data to or from the connected devices (targets/slaves).
It's a **half-duplex** protocol, meaning **only one device talks at a time**, either sending or receiving, not both. In contrast, **SPI is full-duplex** and needs **four lines**, making it more complex.
I²C allows a single master to control communication. Each slave device is identified using a **unique address**, which makes it possible to have **multiple devices on the same bus**.
The communication lines (SDA and SCL) use an **open-drain** system, so **pull-up resistors** are needed to keep the lines HIGH when no one is pulling them LOW.

## Open-Drain Connection
Both the SDA (data) and SCL (clock) lines in I2C use something called **open-drain connections**, which are controlled by NMOS transistors inside the devices.
- When the NMOS transistor **turns ON**, it connects the line to ground, pulling the line voltage **low** quickly.
- When the NMOS transistor **turns OFF**, it stops pulling the line down. Then, a **pull-up resistor** connected to the positive voltage (VDD) slowly pulls the line voltage **high**.
Because the line is only actively pulled down but not actively driven high, the **rising edge (low to high)** of the signal is slower and depends on the resistor and the total capacitance (like the “weight” or “load”) on the line. The falling edge (high to low) is fast because the transistor pulls the line straight to ground.
The speed of the I2C communication depends on this balance:
- A **smaller pull-up resistor** makes the line rise faster, allowing faster communication, but uses more power.    
- A **larger pull-up resistor** saves power but slows down the rise time, making communication slower.
Also, more devices or longer wires add capacitance, which slows down the signal and limits the speed and length of the I2C bus.

## Communication sequence
- Idle state - SDA & SCL - HIGH
- START condition - first SDA - LOW - then - SCL - LOW ⇒ reduces risk of contention as one node is now the master by “claiming the bus” ⇒ this node also starts the clock
- 7-bit slave Address (usually configurable partially via external address lines or jumpers) - Sent MSB first
![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXc-hVgoI_JbwrnwqaUkzdyQCWq1GTIKWx9S0bwmwssVmCtXfyYXhi5UEzY0idtv3N6lvVHoHn-VsA4vZl5zRq27dDtXB4FBGfzky9CY5DiHuOKV5f6JUq1L4u-3jdzbhs3GKRjWrw?key=jE-ynQ9rlYMhfBxFsbcH2w)  
- Read/Write Bit - follows slave address - set by master to indicate desired operation - R/W bit = 0 (write), 1 (Read)
- ACK/NACK - receiver pulls SDA low(ACK) after every byte
ACK - Acknowledge bit - sent by receiver of a byte of data - 0
NACK - negative acknowledgement - Lack of response - 1
ACK - used after slave address and each data byte
- NACK (SDA remains HIGH) used to end communication or signal error
- Data byte transfer - 8 bits per byte, MSB first - after each byte, receiver sends ACK/NACK 
![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXd-CpCJ8xDtBGpHx9O-4vWg3bA71jTdVHPDJVMfQs7lihYBTTHYDpHTWA0wNGnVAy-nqGhVW8jNrCtI5sILtMvHpVdfMTvwQkTYPBmL_ok8y1dbASDeAzPo_3TIR5Ggyw0saavS?key=jE-ynQ9rlYMhfBxFsbcH2w)
Data byte contains info being transferred between master and slave
- STOP condition - SCL - returns and remains HIGH - SDA - returns and remains HIGH
![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXc2aOoVPwJM_qfqniz_0-sC_H-aB1tEh-vfO88QR36hzIQJr-3Bny4AE439jqRJ6KO14sNF_eQAtets-zmKqMGUp7dRbhKQt9LoHSzroXoVnUavy3FQLD8G6P7Adqoi6tm_el_jnw?key=jE-ynQ9rlYMhfBxFsbcH2w)

## I2C Protocol
- **I2C START and STOP Conditions**  
Communication on the I2C bus begins when the controller (master) sends a **START condition** to claim the bus. This happens by pulling the SDA line low first, then pulling the SCL line low. This signals other devices to pause communication and lets the controller take control.
When communication is finished, the controller sends a **STOP condition** by releasing SCL high first, then releasing SDA high. This frees the bus for other devices to use.
* **Logical Ones and Zeros**  
Data on the I2C bus is sent as a series of bits on the SDA line, synchronized by pulses on the SCL clock line. A **logical ‘1’** is when SDA is released (line pulled high by a resistor), and a **logical ‘0’** is when SDA is actively pulled low by a device. For a bit to be valid, SDA must stay stable while SCL is high. Any SDA change during SCL high signals either a START or STOP condition.
* **I2C Communication Frames**  
I2C communication is divided into frames:
**Address Frame:** Sent right after START, contains a 7-bit device address plus a Read/Write (R/W) bit (0 for write, 1 for read). This lets the controller specify which device it wants to talk to and whether it wants to send or receive data. 
**Data Frames:** One or more bytes of data follow the address frame. 
Each frame is followed by an **ACK (acknowledge) bit** where the receiver pulls SDA low to confirm it successfully received the data. If no ACK is received (called NACK), it means the device didn’t get the data or the address was wrong.
After all data is sent, the controller sends the **STOP condition** to release the bus.

**List of reserved I2C addresses**
![[speed.png]]
## Advantages 
- Only 2 wires for many devices
- Simple wiring
- Supports multiple masters/slaves
## Cons
- Limited data rate (~3.4 Mbps max)
- Limited cable length and speed
- Requires unique addresses
- Shared bus can get congested
- Needs external pull-up resistors
- Slower than SPI
## Ideal for 
- Many devices, fewer pins
- Moderate data transfer
## Avoid when
- High speed data or long distances
- Strict real time requirements
## **CAN**
CAN (Controller Area Network) is a communication protocol designed for robust and fast data exchange between electronic devices (ECUs) inside vehicles and other systems like robotics.
- It’s fast and reliable, perfect for safety-critical systems in cars, electric vehicles, and industrial machines.
- It connects many ECUs (Electronic Control Units) small computers controlling everything from motors to brakes to windows so they can talk to each other.
CAN uses a shared bus topology, meaning many devices (nodes) connect to the same two-wire bus, no master device controlling everything. The two wires are called CAN High and CAN Low, and they’re twisted together to reduce electromagnetic interference (EMI). The signal on the bus is the difference in voltage between CAN High and CAN Low  this differential signaling makes the communication very noise-resistant. At each end of the bus are terminating resistors (usually 120 ohms) to prevent signal reflections that cause errors.

**How Do Nodes Avoid Talking Over Each Other?**
When multiple ECUs want to send data simultaneously, CAN uses a clever system called arbitration:
- Every node has a unique ID number.
- When two or more nodes start sending at the same time, they send their ID bits bit-by-bit.
- In CAN, a 0 bit is dominant over a 1 bit, so if one node sends a 0 while another sends a 1, the one sending the 1 must stop transmitting => it lost arbitration.
- This means the node with the lowest ID (highest priority) wins and gets to send its message first.
- Nodes detect whether they’ve won by reading back what they sent and comparing it to the bus state.

## Communication Sequence
The CAN (Controller Area Network) communication process begins when the bus is in an Idle State, where both CAN High and CAN Low lines remain at a recessive voltage level. This indicates that no communication is taking place and the bus is free for any node to initiate a transmission.

When a node wants to transmit data, it signals the Start of Frame by driving a dominant bit (logical 0) onto the bus. This transition marks the beginning of a message and alerts all other nodes to monitor the transmission.

Following this, the bus enters the Arbitration Phase, which ensures that only one node transmits at a time. Each node transmits its message ID bit-by-bit while simultaneously monitoring the bus. Due to the dominant bit having priority over the recessive bit, the node with the lowest numerical ID continues transmitting, while others detect a mismatch and immediately stop, deferring their transmission. This mechanism guarantees non-destructive priority-based access.

Once arbitration is complete, the winning node sends the Control Field, which includes important information such as the Data Length Code (DLC)—indicating how many bytes of data will follow. This is crucial for all listening nodes to know how much data to expect.

The Data Field comes next and contains the actual payload, typically up to 8 bytes in classical CAN and up to 64 bytes in CAN FD (Flexible Data rate). This field carries the information relevant to the operation of the system, such as sensor values, actuator commands, or status updates.

To ensure data integrity, the CRC Field (Cyclic Redundancy Check) is included. This field allows all receivers to verify whether the message was received without errors. The sender calculates a CRC value based on the message, and receivers compare it to their own calculation of the CRC.

After the CRC check, the ACK Field is transmitted. All receivers who correctly received the message will drive a dominant bit in this field to acknowledge receipt. The transmitter checks this bit to confirm successful delivery. If no acknowledgment is received, the transmitter assumes an error occurred and may attempt retransmission.

Finally, the message ends with the End of Frame, a sequence of recessive bits indicating that the bus is free again. A short Inter-frame Space follows, acting as a buffer period before any new transmission can begin.

## Main components
A typical CAN communication system involves several key hardware components that work together to ensure reliable data transfer between electronic control units (ECUs). The most fundamental parts include the **microcontroller**, the **CAN controller**, and the **CAN transceiver**.
At the core of the system is the **microcontroller (MCU)**. It runs the application logic, processes sensor inputs, and makes decisions. However, it cannot directly communicate over the CAN bus lines. That’s where the **CAN controller** comes in. The CAN controller is responsible for creating and interpreting CAN frames it handles message formatting, arbitration, error detection, and filtering. Many modern microcontrollers include an integrated CAN controller. If not, an external CAN controller (like the MCP2515) can be used.
To physically transmit and receive signals over the bus, a **CAN transceiver** is required. This component translates the digital data from the CAN controller into differential voltage signals suitable for the CAN bus (CAN High and CAN Low). It also receives those differential signals and converts them back into standard logic levels for the controller to process. Commonly used transceiver chips include the **SN65HVD230**, **TJA1050**, and **MCP2551**. These are critical for ensuring electrical compatibility and signal robustness across the network.
The **CAN bus** itself consists of a twisted-pair cable, one for **CAN_H** and one for **CAN_L** to carry the differential signal. To maintain signal integrity and avoid reflection at the ends of the transmission line, **termination resistors** (typically 120 ohms) are added at both ends of the bus.
A complete CAN node includes:
- A **microcontroller** (for application logic),
- A **CAN controller** (for protocol handling),
- A **CAN transceiver** (for voltage-level conversion),
- **Bus wires** (twisted pair for CAN_H and CAN_L),
- And **termination resistors** (for signal stability).
## Physical Layer = How the signal travels on wires?

The physical layer is the part of CAN that deals with how data actually moves across wires. It uses two special wires called CAN High and CAN Low, which carry opposite signals. Instead of just sending 1s and 0s like regular digital systems, CAN sends the difference between these two wires—this helps make it super resistant to noise or interference from the environment. When there's a 2-volt difference between the wires, that's read as a “0” (called dominant), and when the voltages are almost the same, that’s a “1” (called recessive). These wires are twisted together and have resistors at both ends to keep the signals clean and prevent weird reflections. A small chip called a CAN transceiver handles all this and makes sure the signals are properly sent and received.
**![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXcoxUFU7ZpOW44E_nIw0VLDprQQQdiW9S6GjFAbT0yoPRuXI8BP4LvrXAMrE_AEROsUsB5WLAucHyx3ARS7BtsHPthlmiUPvzz1UA8hSlZzzxCXTfaZsX3nirSiP2-nC3WERgIb?key=jE-ynQ9rlYMhfBxFsbcH2w)**

## Data Link Layer = How messages are packed and handled?

The data link layer is in charge of how messages are built, sent, and checked on the CAN network. It decides how the message should start, how long it is, and what data it includes. When multiple devices try to talk at once, it uses a clever method called arbitration to make sure only one device sends at a time, usually the one with the most important message. The message includes things like the ID (who’s sending it), how much data is being sent, the actual data, a CRC (error-checking code), and an ACK (a small “got it” signal from receivers). This layer makes sure the communication is smooth, no one talks over each other, and any errors are caught and corrected.
**![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXdQVJUiKfSsjUduchwxDfGxyZWIuIW8c-NTFSO_UCVlEFlOAhWqnEALc-36OAN9yVXkuSbakiRSvsx_6YuGSXMOdanK9O_NIPfKqpZzUj7mxZK2JwL2lKaFR9qjSs5b3_WdZIHq?key=jE-ynQ9rlYMhfBxFsbcH2w)**

## **Differential Pairs & Signaling**

Single-ended signaling uses one wire to carry signal voltage from microcontroller to sensor, referenced to common ground. Examples include I²C, SPI, GPIO. Transmitter sends voltage on wire; receiver reads voltage relative to ground. Issues arise with long-distance or noisy environments—electromagnetic interference, crosstalk. Ground potential difference between sender and receiver causes ground offset. Receiver voltage becomes signal voltage plus ground offset, leading to distortion and errors.

Differential signaling solves ground offset and noise issues by sending two opposite signals on paired wires. One wire carries original signal voltage, the other carries its inverted voltage. At receiver, subtracting these signals doubles the signal and removes common ground offset and noise, since both wires share the same interference. This improves signal integrity over longer distances and noisy environments.

True differential pair uses two insulated wires twisted together, like Ethernet cables. This 3D twisting causes both wires to pick up noise equally, so interference cancels out naturally. No separate ground wire is needed because electromagnetic fields are tightly linked between the wires, giving excellent noise immunity.

PCB differential pair uses two traces routed side by side on a flat board. Here, coupling is weaker than twisted wires because each trace mainly couples to the ground plane underneath rather than each other. Noise can affect the two traces differently, making it less ideal. Still, with careful PCB layout, this planar method works well for on-board high-speed signals.

Each single-ended trace has an impedance Z_0​ relative to the ground plane. Differential impedance Z_diff​ depends on this single-ended impedance and the coupling between the two traces, called Z_coupling​. The approximate relationship is:
Zdiff ≈ 2 * Z_0 − 2 * Z_coupling​
When traces are placed closer, coupling increases, which lowers the differential impedance Z_diff.

Wider traces let more electric charge flow, so they have less resistance to the signal. When two traces are closer together, they “talk” more to each other, which also lowers the resistance between them. So, thin traces close together have low resistance, and wide traces far apart have higher resistance.

For example, in PCI Express cables, each trace usually has about 45 to 50 ohms resistance, and the pair together has about 85 ohms. To make this happen, you pick the trace width first, then change the space between the two traces until you get the right resistance. Programs like Altium can help with this.

It’s important that both traces in a pair are the same length so signals arrive at the same time. If one trace is longer, its signal arrives late, this is called “skew,” and it can cause errors. To fix this, designers add small loops to the shorter trace to match lengths. For many pairs in one design, small timing differences between pairs aren’t as big a problem, so those traces can be routed more freely.


## **CRC: Cyclic Redundancy Check**

While sending a message, like a long string of numbers or bits, over a wire or wireless connection. Sometimes, noise or interference can cause some bits to flip from 0 to 1 or 1 to 0, which can mess up the message. To catch these errors, we use something called **CRC**, which acts like an error detector.

Before sending the message, the sender takes the whole message and divides it by a fixed number called a **polynomial**. This division is done in binary using special rules. The remainder from this division is a short string of bits called the **CRC code** or **CRC checksum**.

The sender attaches this CRC code to the end of the original message and sends both together.

When the receiver gets the message plus CRC code, it does the same division using the same polynomial on the combined data (message + CRC). If everything is perfect and no bits got changed, the remainder will be zero. This means the message is error-free.

If the remainder is not zero, it means there was an error during transmission, so the receiver knows the data is corrupted and can ask for the message to be sent again.

Uses:
- It catches many types of common errors, like single-bit errors, burst errors (where a group of bits are corrupted), and others.
- It’s fast to compute using simple hardware or software.
- It helps improve the reliability of communication systems like Ethernet, USB, and many others.

CRC is a smart way to add a small “check code” to your message so the receiver can tell if the message arrived safely or if something went wrong during transmission.

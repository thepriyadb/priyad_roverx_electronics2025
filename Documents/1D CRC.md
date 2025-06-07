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

Learning by answering questions:

**How is CRC mathematically defined?**
It is a linear block code => Linear -> If we XOR 2 valid CRC-encoded messages, you get another valid one. Block Code -> Operates on fixed length blocks of data.
Instead of treating data bits as just numbers, CRC represents them as a binary polynomial. For example, the binary message 1011 is interpreted as polynomial M(x) = $x^3$ + $x$ + $1$ .
General polynomial G(x) is a predefined polynomial known to both the transmitter and receiver. It is also represented as binary. 
G(x) = $x^3$ + $x$ + $1$  
The degree of G(x) determines the number of CRC bits (let's call this n). So, for G(x) of degree 3 -> CRC = 3 bits.

You want to transmit a message such that the receiver can check for errors just by doing a division.
T(x)=M(x)⋅$x^n$⊕R(x)
M(x)⋅$x^n$ - means appending n zeros to the message -> shift left operation
The remainder of the division is called R(x), this is the CRC.
T(x) is the actual message that is transmitted over the wire.

Receiver takes the received message T(x) and divides it by the G(x).
If remainder is 
= 0 -> message is assumed correct
≠ 0 -> **error detected**

**What kind of polynomial is used for CRC generation?**
A generator polynomial G(x) whose degree determines CRC length. Examples,
CRC-8 : G(x) = $x^8 + x^2 + x + 1$
CRC-16 : G(x) = x¹⁶ + x¹² + x⁵ + 1
CRC-32 : G(x) = x³² + x²⁶ + x²³ + … + 1 (used in Ethernet)

**How is a CRC code generated from the original data bits?**
Consider D(x) as your data bits as a binary number. 
G(x) as the generator polynomial in binary.
n as the degree of G(x) => number of CRC bits.

Firstly, append n zeros to data. For example, let
data = 1101 (4 bits)
G(x) = 1011 -> degree 3 => n=3
So after appending data is -> 1101000

Now, divide the appended data by G(x) using mod-2 division which is similar to regular division but uses XOR instead of subtraction.
For example, 1101000 by 1011 gives 011

Now append remainder to the original data.
It gives 1101011. (example)

**How does CRC detect errors?**
CRC detects errors by checking if the received bitstream is divisible by G(x) that was used at the transmitter.
Receiver takes the received message T(x) and divides it by the G(x).
If remainder is 
= 0 -> message is assumed correct
≠ 0 -> **error detected**

**What types of bit errors can CRC reliably detect?**
The strength of CRC depends on degree and design of the generator polynomial G(x). Commonly used CRCs CRC-16, CRC-32 can detect:
- all single bit errors, if G(x) has at least 2 non-zero terms
- all double bit errors, if G(x) doesn't divide $x^k + 1$ for any small k.
- all odd-numbered bit errors, if G(x) has x+1 as a factor.
It may not detect:
- where error polynomial is a multiple of G(x) which has the probability of 1 in $2^n$

**How is CRC implemented in digital communication systems?**
CRC is implemented as a mathematical mechanism to detect data corruption during transmission. It is used in systems like Ethernet, CAN, USB, HDLC, SD cards, Flash memory, and embedded protocols.

**At which layer of the OSI model is CRC typically applied?**
It is applied primarily at the Data Link layer of the OSI model fro framing, addressing, error detection.

**Is CRC computed in hardware, software, or both?**
Both implementations exist depending on system's speed, resources, and use case.
 **Hardware CRC:**
- **Used in high-speed, real-time systems** (Ethernet PHYs, CAN transceivers, FPGAs).
- Often implemented using:
    - **LFSRs (Linear Feedback Shift Registers)** - Should learn about this
    - XOR networks with flip-flops
    - CRC generator logic inside chips (e.g., STM32 CRC peripheral)
**Software CRC:**
- Used in microcontrollers, low-speed or simple protocols, or testing tools. 
- Computed using:
    - Bitwise CRC calculation (slow but flexible)
    - **Lookup tables (LUTs)** for speed optimization (e.g., CRC-32 with 256-entry table)

**What are CRC-8, CRC-16, CRC-32?**
CRC-8 -> 8 bits -> used in I2C
CRC-16 -> 16 bits -> used in CAN, USB
CRC-32 -> 32 bits -> used in Ethernet

**How do you choose a CRC polynomial?**
Based on message length, error model, system speed.

**Can CRC fail to detect certain errors?**
Yes. It misses error when the received frame with error happens to be divisible by generator polynomial G(x), known as CRC collision. It also misses out when the errors are structures or repeatable.

**Can CRC be used for error detection and correction?**
No. For that it must be combined with error-correcting codes ECC or retransmission protocols.

## **Differential Pairs & Signaling**

Single-ended signaling means transmitting data using a single conductor (=>wire) where the signal voltage is measured relative to a common reference point, usually ground.
Why is the ground reference important?  
The receiver interprets the signal by comparing the voltage on the signal line to the voltage on the common ground. Without a stable reference, signal interpretation becomes unreliable.
The microcontroller acts as the transmitter, outputting voltage signals, and the sensor acts as the receiver, detecting these voltage changes. Examples include I²C, SPI, GPIO. 

Transmitter sends voltage on wire. It operates by driving the line high or low by outputting corresponding voltage levels referenced to ground. Receiver reads voltage relative to ground. It interprets data by measuring the voltage difference between the signal wire and ground, the receiver decodes the intended logic state.

Issues arise with long-distance or noisy environments like EMI, crosstalk.  The voltage at the ground reference of the transmitter differs from that at the receiver due to voltage drops, noise, or grounding issues. The receiver measures signal voltage plus any offset in ground potential, distorting the intended signal level. Receiver voltage becomes signal voltage plus ground offset, leading to distortion and errors. The distorted voltage can cause the receiver to misinterpret bits, resulting in data errors like Bit flips, loss of synchronization, or complete communication failure.

Differential signaling solves ground offset and noise issues. It is a signaling method where two complementary signals are sent simultaneously on two separate but closely coupled conductors (wires). Because the receiver looks at the voltage difference between the two wires, any common shift in ground potential affects both lines equally and cancels out when the difference is taken.

One wire carries original signal voltage, the other carries its inverted voltage. Inverted voltage is when, if the first wire has a voltage level representing a logic ‘1’, the second wire has the opposite voltage representing a logic ‘0’. The transmitter drives one wire with the signal and the other with the logical complement, usually through a differential driver circuit.
 
  At receiver, subtracting these signals doubles the signal and removes common ground offset and noise, since both wires share the same interference. The receiver measures the voltage difference (V+ minus V−), which enhances the signal amplitude and rejects noise common to both wires. Interference or voltage offsets that appear identically on both wires simultaneously, such as electromagnetic interference or ground shifts. Since noise affects both lines equally, when the receiver subtracts one line voltage from the other, the noise cancels out. 
  Why does this double the signal?  
  Because one line goes high while the other goes low, the difference between them is effectively twice the amplitude of the single-ended signal.

 This improves signal integrity ( The ability of a system to transmit signals without distortion, errors, or loss) over longer distances and noisy environments.
 
 True differential pair (It consists of two wires physically twisted around each other, each carrying complementary signals) uses two insulated wires twisted together, like Ethernet cables. This 3D twisting causes both wires to pick up noise equally, so interference cancels out naturally. No separate ground wire is needed because electromagnetic fields are tightly linked between the wires, giving excellent noise immunity.
 
 PCB differential pair (On a printed circuit board (PCB), differential signals are routed using two parallel copper traces that carry equal and opposite signals) uses two traces routed side by side on a flat board. 
 Why side by side?
 This physical proximity allows for electromagnetic coupling between the traces, enabling differential signaling on a flat 2D substrate like a PCB.
 How is this different from twisted pairs?
 Unlike twisted wire pairs (3D routing in space), PCB differential pairs are planar and follow straight or curved paths on defined board layers.
 Here, coupling (Coupling refers to the electromagnetic interaction between the two traces and how effectively changes in one affect the other) is weaker than twisted wires because each trace mainly couples to the ground plane underneath rather than each other. Noise can affect the two traces differently, making it less ideal. Still, with careful PCB layout, this planar method works well for on-board high-speed signals.
 Why is it still effective?
 For short, controlled distances on a PCB (as opposed to long cables), well-routed differential pairs offer sufficient performance for high-speed signals (USB, HDMI, PCIe, etc.).
 
 Each single-ended trace has an impedance *Z_0* relative to the ground plane. Z₀ is the impedance of a single signal trace with respect to a reference ground plane. Signal reflections and distortion occur when the trace impedance does not match the source/load impedance. Maintaining Z_0 ensures signal integrity, especially for high-speed signals. *Differential impedance Z_diff*​ depends on this single-ended impedance and the coupling between the two traces, called *Z_coupling​*. 
 Z_diff is the impedance experienced by a pair of differential signals traveling on two traces. Z_coupling refers to the mutual electromagnetic interaction between the two traces of a differential pair. The closer the traces the stronger the coupling, lower the Z_diff. Stronger coupling increases mutual capacitance and mutual inductance, which effectively reduces Z_diff.
 The approximate relationship is:
 *Zdiff ≈ 2 * Z_0 − 2 * Z_coupling​* 
 - *Increase spacing → weaker coupling → higher Z_diff
- *Decrease spacing → stronger coupling → lower Z_diff*

 Wider traces let more electric charge flow, so they have less resistance to the signal. When two traces are closer together, they interact more with each other, which also lowers the resistance between them. So, thin traces close together have low resistance, and wide traces far apart have higher resistance.
 
 For example, in PCI Express cables, each trace usually has about 45 to 50 ohms resistance, and the pair together has about 85 ohms. To make this happen, you pick the trace width first, then change the space between the two traces until you get the right resistance.
 It’s important that both traces in a pair are the same length so signals arrive at the same time. If one trace is longer, its signal arrives late, this is called “skew,” and it can cause errors. To fix this, designers add small loops to the shorter trace to match lengths. For many pairs in one design, small timing differences between pairs aren’t as big a problem, so those traces can be routed more freely.

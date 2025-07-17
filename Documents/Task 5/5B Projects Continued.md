Some questions:

The *baud rate* is the speed of communication between your Arduino and your computer (via Serial Monitor).
Why 9600? Standard/ default baud rate.

A *serial port* is a communication interface that sends data one bit at a time, in a sequence serially from one device to another. It’s how your Arduino talks to your computer, and vice versa.

### PROJECT 4:

When I input a number (example, 5) in serial monitor in Arduino IDE, the 6 LEDs blink those number (example, 5) of times.

![](LEDPWM4.png)

for example, 
Input in Serial Monitor: 7
Output:

![](sketch_4.mp4)

### PROJECT 5:

When I input (LED_number Number_of_times_to_blink) (example, 1 5 ) in the serial monitor then the LED blinks the mentioned number of times.

![](LEDPWM5.png)

for example,
Input on Serial Monitor: 3 7
Output:

![](sketch_5.mp4)

PROJECT 6:

Write a program that takes an array of tuples like { (0,100), (2,155) } as input, where each tuple represents an LED pin number and a PWM value. The program should blink each LED by turning it ON at the specified PWM value for 500 milliseconds and then OFF for 500 milliseconds, without using delay().

Input : Array of Tuples
example, {(2,155), (4,100)}
Where, each tuple represents LED pins and PWM value
The program blinks each LED by turning it ON at specified pwm value for 300 milliseconds and OFF for 300 milliseconds without using delay()

Update:
Tried using 2 different approaches
- 2D Array to hold LED data like pin number, brightness, state
- Normal Parallel Array for LED data

Both used similar logic 
Input from Serial monitor --> Removing brackets, comma --> extracting LED data --> Storing values in arrays --> Initial State --> loop to identify LED --> LED blinks as mc follows instructions 

![[Pasted image 20250702200638.png]]
![[Pasted image 20250702200711.png]]
![[Pasted image 20250702200744.png]]


2D  array
![[Pasted image 20250702200813.png]]
![[Pasted image 20250702200848.png]]
![[Pasted image 20250702200905.png]]


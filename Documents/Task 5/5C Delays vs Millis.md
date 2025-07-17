# delay()

## Functionality
The delay() function pauses the execution of the Arduino program for a specified number of milliseconds. During this pause, the microcontroller does absolutely nothing except wait.
## Syntax
delay(milliseconds);

Where milliseconds is the duration of the pause in milliseconds (an unsigned long integer).

## Example
void setup() {
  pinMode(13, OUTPUT); // Define digital pin 13 as an output
}
void loop() {
  digitalWrite(13, HIGH);   // Turn the LED on (HIGH is the voltage level)
  delay(1000);               // Wait for 1000 millisecond(s) (1 second)
  digitalWrite(13, LOW);    // Turn the LED off by making the voltage LOW
  delay(1000);               // Wait for 1000 millisecond(s) (1 second)
}

This code will make the LED connected to pin 13 blink on and off every second.
## Advantages
- **Simplicity:** delay() is very easy to understand and use, making it suitable for simple tasks and beginners.
- **Straightforward Timing:** It provides a direct and predictable way to introduce pauses in the program flow.
## Disadvantages
- **Blocking:** The primary disadvantage of delay() is that it is a _blocking_ function. While the program is delayed, the microcontroller cannot perform any other tasks. This means that the Arduino becomes unresponsive to inputs and cannot execute other code during the delay period.
- **Inefficiency:** Using delay() can lead to inefficient code, especially in applications that require multitasking or real-time responsiveness.
## Use Cases
- **Simple Blinking LEDs:** Basic examples where precise timing is not critical.
- **Debugging:** Temporarily pausing the program flow to observe variable values or debug code.
- **Non-Critical Timing:** Situations where the Arduino does not need to respond to external events during the delay.

# millis()

## Functionality
The millis() function returns the number of milliseconds that have passed since the Arduino board started running the current program. This value overflows (resets to zero) after approximately 50 days.
## Syntax
unsigned long currentTime = millis();
The return value is an unsigned long integer.

## Example
unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval = 1000;        // interval at which to blink (milliseconds)
void setup() {
  pinMode(13, OUTPUT);
}
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // if the LED is off turn it on and vice versa:
    digitalWrite(13, digitalRead(13) == LOW ? HIGH : LOW);
  }
}
This code achieves the same blinking LED effect as the delay() example, but without blocking the program execution.
## Advantages
- **Non-Blocking:** millis() is a _non-blocking_ function. It returns the current time without pausing the program execution. This allows the Arduino to perform other tasks while keeping track of time.
- **Multitasking:** Enables the implementation of multiple tasks that run concurrently, as the Arduino can check the elapsed time and perform actions accordingly.
- **Responsiveness:** The Arduino remains responsive to inputs and external events while using millis() for timing.
## Disadvantages
- **Complexity:** Using millis() for timing requires a slightly more complex logic compared to delay().
- **Overflow:** The millis() value overflows after approximately 50 days, which needs to be considered in long-running applications. However, the subtraction method used in the example code handles the overflow correctly.
## Use Cases
- **Multitasking Applications:** When the Arduino needs to perform multiple tasks simultaneously, such as reading sensors, controlling motors, and responding to user input.
- **Real-Time Systems:** Applications that require precise timing and responsiveness to external events.
- **Long-Running Programs:** Programs that need to run for extended periods without blocking.
- **Interrupt-Driven Systems:** millis() can be used in conjunction with interrupts to perform time-based actions.


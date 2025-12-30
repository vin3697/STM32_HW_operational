# Understanding Embedded C: Passing Arguments by Address

When controlling hardware (like GPIO), we don't pass the "actual hardware" to a function. Instead, we pass the **Memory Address** of where that hardware lives.

## 1. The Core Concept: Port vs. *Port
In C, the asterisk (`*`) has two different meanings depending on where you see it:

* **`GPIO_TypeDef *port` (In the Function Header):**
    The `*` is just a **label**. It tells the computer: "The variable named `port` is a container that holds a memory address."
* **`port` (Inside the Function):**
    This is the **Address** itself (the GPS coordinates). We pass this to HAL functions so they know which "mailbox" to talk to.
* **`*port` (Dereferencing):**
    This is the **Hardware** inside that address. We rarely use this directly; we usually just pass the address (`port`) to the HAL.

## 2. The GPS Analogy
* **`port`**: The GPS coordinates (e.g., `34.05, -118.24`).
* **`*port`**: The actual house sitting at those coordinates.

When we call `HAL_GPIO_TogglePin(port, ...)`, we are giving the HAL the **GPS coordinates** and saying, "Go to this location and flip the switch."

## 3. Why We Use Arguments
By passing the address as an argument, we make the code **reusable**. One function can control any LED on any port just by changing the "note" we hand to it:

```c
// Same function, different "GPS coordinates"
control_LED(GPIOA, GPIO_PIN_5); // Controls LED on Port A
control_LED(GPIOB, GPIO_PIN_0); // Controls LED on Port B
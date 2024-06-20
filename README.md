# tinyamp

## The Idea
This project ist for a small guitar amplifier controlled with a small 8-bit microcontroller. The Amplifier and effect circuits are analoge, but all potentiometers are replaced by digital potentiometers, which are controlled by the MCU.
The circuits are a mixture of some of the circuits of https://www.electrosmash.com/ 

## What's needed?
* I2C Driver for the Potentiometer (Non-blocking, with polling, uses a simple ring buffer)
* Digital Potiometer control
* Virtual Potentiometers
* Rotary Encoder evaluation
* LED control
* timers. 
* Real-time scheduler
* User Control State Charts

## Coding
* Coding is done in C++ usung a lot of template stuff, the basic setup follows many of the ideas of the book  [Real-Time C++](https://link.springer.com/book/10.1007/978-3-662-62996-3)
* I also try to follow some of the principles of the insightfull book [Clean Architecture: A Craftsman's Guide to Software Structure and Design](https://www.oreilly.com/library/view/clean-architecture-a/9780134494272).

## Status
The I2C driver, and the basic control of the digital potentiometers are working as well as the decoding of the rotary decoders. Next steps are the implementaion of the virtual potentiometers and of the real time scheduler



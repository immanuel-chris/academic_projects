3×3×3 LED Cube using AVR ATmega328P and Bare-Metal C
EEE184 Project
Submitted by: Chris Immanuel I. Arcasa


Project Description

This project demonstrates the design and implementation of a 3×3×3 LED Cube controlled by an AVR ATmega328P microcontroller. The cube contains 27 LEDs arranged in a 3D matrix (3 layers × 9 columns), capable of displaying dynamic animations through efficient software-based multiplexing. Each LED is addressed by activating a specific column and layer combination, creating the illusion of simultaneous lighting using persistence of vision.

The system is programmed in bare-metal C (no Arduino libraries), using direct register manipulation for optimal performance and control. Animations/patterns are implemented to showcase real-time LED control and low-level embedded system design.

The project serves as both an educational tool and a visual display, illustrating core embedded concepts like GPIO control, timing accuracy, and minimal hardware design using only 12 I/O pins.


Key Features

- AVR ATmega328P @ 16 MHz (bare-metal C, no Arduino libs)
- 3×3×3 LED matrix (27 total LEDs)
- 12 GPIOs used: 9 columns, 3 layers
- Software multiplexing for smooth animations
- Animation patterns: wave, rain, diagonal, triangle ripple
- Manual wiring on perfboard with 220Ω resistors
- No external libraries or drivers used



Files

- 'ledCube.c' — Main control logic for LED cube animations
- 'Makefile' — For compiling and flashing (optional)
- 'README.md' — Project description and setup instructions



Educational Value

This project provides a hands-on introduction to:
- AVR register-level programming
- Multiplexing and timing techniques
- Embedded systems hardware-software integration



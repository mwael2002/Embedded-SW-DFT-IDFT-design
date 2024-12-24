# Embedded-SW-DFT-IDFT-design
## This project aims to test software implementation of DFT & IDFT on STM microcontroller
### Project Phases:
#### First: Generating the sinusoidal signals with desired frequencies by Matlab then importing them in the project and plotting them on Arduino serial plotter via UART.
#### Second: Implementation of DFT algorithm and applying it on the inputs then plotting them same as the previous way.
#### Third: Implementation of IDFT algorithm and applying it on the output of DFT then plotting output of IDFT same as the previous ways.
#### Hardware: STM32 Nucleo board
#### Drivers used: FPU and USART.
### An example of signal has 1KHz & 15KHz freq. components:
#### 1- Input Signal
![Alt text](https://github.com/mwael2002/Embedded-SW-DFT-IDFT-design/blob/main/Screenshot%202024-08-06%20175017.png)
#### 2- DFT Output:
![Alt text](https://github.com/mwael2002/Embedded-SW-DFT-IDFT-design/blob/main/Screenshot%202024-08-06%20175419.png)
#### Note: The x-axis isn't correct as arduino plotter puts it by itself
#### 3- IDFT Output:
![Alt text](https://github.com/mwael2002/Embedded-SW-DFT-IDFT-design/blob/main/Screenshot%202024-08-06%20175702.png)

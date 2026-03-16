# UWB Positioning System - software
This folder contains files associated with software of the UWB Positioning System.

## Table of contents
* [Naming convention](#naming-convention)
* [General info](#general-info)
* [Project structure](#project-structure)
* [Setup](#setup)
* [Technologies](#technologies)

## Naming convention
- A UWB anchor is also referred to as a "lighthouse".
- The UWB tag is also referred to as an "observer"
- The module that read data from the tag is also referred to as a "sailor"

## General info
- At least four anchors are needed for positioning a tag.
- The anchors automatically determine their relative position in around 30 seconds after power-up
- Simulation of the effectiveness of the system.
- Implementation a low-level I2C communication between an STM32 and an LCD, for visualization and testing purposes.

## Project structure
- The [LighthouseESP](LighthouseESP/) folder contains code that is uploaded to an ESP32 anchor.
- The [Observer](Observer/) folder contains code that is uploaded to an ESP32 tag.
- The [Sailor](Sailor/) contains code uploaded to an STM32 module, connected to tag via UART.
- The [MATLAB_Simulations](MATLAB_Simulations/) contains the simulation files and results.

## Setup
To run this project, upload the [LighthouseESP](./LighthouseESP/) code to an ESP32, connected to a DWM1000 as discussed in the [Hardware](/Hardware/) part. Similarly upload the [Observer](./Observer/) code to an ESP32 + DWM1000 module. Then follow the setup instructions given in the [LighthouseESP](./LighthouseESP/) folder.

## Technologies
Programming languages:
- C
- C++
- MATLAB

Tools used:
- STM32 Cube IDE
- PlatformIO
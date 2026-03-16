![IT](https://img.shields.io/badge/IT-purple)
![Robotics](https://img.shields.io/badge/Robotics-orange)
![Electronics](https://img.shields.io/badge/Electronics-darkred)

![Hardware](https://img.shields.io/badge/Hardware-blue)
![Software](https://img.shields.io/badge/Software-lightblue)

# UWB Positioning System
An indoor positioning system based on the Ultra-Wideband technology. It allows centimeter-accurate positioning of a moving tag, specifically designed for UAVs.

Created both software and hardware.

Author: Arkadiusz Rozmarynowicz.

## Table of contents
* [General info](#general-info)
* [Project structure](#project-structure)
* [Important note](#important-note)
* [Motivation](#motivation)
* [Technologies](#technologies)
* [Setup](#setup)
* [Roadmap](#roadmap)

## General info
- A communication system consisting of a moving tag and at least four ranging anchors.
- The tag and anchors are based on an DWM1000 ranging module and an ESP32.
- Implemented an algorithm for least square error estimation of the 3D coordinates, based on uncertain distance measurements.
- Designed and built a custom PCB with a 3D printed casing.
- Simulated and visualized the process in MATLAB.
- Created a Doxygen documentation.

## Project structure
The project has been split into two parts: hardware and software, that are available in the [Hardware](/Hardware/) and [Software](/Software/) folders, along with more details on each part.

[MATLAB simulations](/Software/MATLAB_Simulations/) are available in the [Software](/Software/) folder.

## Important note
As the project has been developed by me logged into a different account, the majority of commits come from "RocketEquation" and "arozmary" accounts, both of which belong to me.

## Effects
The system allows for positioning a slow-moving tag with an accuracy better than 25 centimeters. Effectiveness with a fast-moving tag has not yet been tested (see [roadmap](#roadmap)).

## Motivation
As I decided on my Bachelor's project (full implementation of a quadcopter) I needed a way to position an UAV in an indoor environment. As I couldn't rely on GPS signal, I decided to create a DIY substitution. I experimented with a few ranging technologies, and finally settled with ultra-wideband beacons.

## Technologies
Programming languages:
- C
- C++
- MATLAB

Communication protocols:
- UWB
- ESP-NOW
- SPI
- UART
- I2C

Tools used:
- STM32 Cube IDE
- PlatformIO
- Altium Designer
- Autodesk Fusion

## Setup
To run the project, please first refer to the details in [Hardware](/Hardware/) folder, and then follow the instructions in the [Software](/Software/) folder.

## Roadmap
- [x] Distance measurements among the anchors
- [x] Automatic 3D estimation of each anchor relative to each other
- [x] 3D position estimation of the tag
    - [x] Least squares method
    - [ ] Weighted least squares method
- [x] PCB and 3D-printed casing
- [x] Test of the setup on a slowly moving tag
- [ ] Integration with an UAV

## License
To be decided.
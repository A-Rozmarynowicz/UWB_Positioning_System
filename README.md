![IT](https://img.shields.io/badge/IT-purple)
![Robotics](https://img.shields.io/badge/Robotics-orange)
![Electronics](https://img.shields.io/badge/Electronics-darkred)

![Hardware](https://img.shields.io/badge/Hardware-blue)
![Software](https://img.shields.io/badge/Software-lightblue)

# UWB Positioning System
An indoor positioning system based on the Ultra-Wideband technology. It allows centimeter-accurate positioning of a moving tag, without relying on GPS signal. Specifically designed for UAVs.

Implemented software, hardware and simulation.

Author: Arkadiusz Rozmarynowicz.

## Table of contents
* [General info](#general-info)
* [Project structure](#project-structure)
* [Important note](#important-note)
* [Effectiveness](#effectiveness)
* [Technologies](#technologies)
* [Setup](#setup)
* [Roadmap](#roadmap)
* [Future](#future)

## General info
- A communication system consisting of a moving tag and at least four ranging anchors.
- The tag and anchors are based on an DWM1000 ranging module and an ESP32.
- The anchors automatically determine their relative position on start-up.
- Implemented an algorithm for least square error estimation of the 3D coordinates, based on uncertain distance measurements.
- Designed and built a custom PCB with a 3D printed casing.
- Simulated and visualized the process in MATLAB.

## Project structure
The project has been split into three parts: software, hardware, and simulation.

- [Software](/Software/) consists of code for the tag and anchors.
- [Hardware](/Hardware/) consists of a PCB project and a 3D-printed casing files.
- [Simulation](/Simulations/) consists of MATLAB code that allows for testing and visualizing different setups.

## Important note
As the project has been developed by me logged into a different account, the majority of commits come from "RocketEquation" and "arozmary" accounts, both of which belong to me.

## Effectiveness
The system allows for positioning a slow-moving tag with an accuracy better than 25 centimeters. Effectiveness with a fast-moving tag has not yet been tested (see [roadmap](#roadmap)).

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
- PlatformIO
- STM32 Cube IDE
- Altium Designer
- Autodesk Fusion

## Setup
To run the project, please first refer to the details in the [Hardware](/Hardware/) folder, and then follow the instructions in the [Software](/Software/) folder.

## Roadmap
- [x] Distance measurements among the anchors
- [x] Automatic 3D estimation of each anchor relative to each other
- [x] 3D position estimation of the tag
    - [x] Least squares method
    - [ ] Weighted least squares method
- [x] PCB and 3D-printed casing
- [x] Test of the setup on a slowly moving tag
- [ ] Integration with an UAV

## Future
The project will play an important role in the development of my Bachelor's project: "Design and implementation of a quadrotor with a localization algorithm based on Ultra-Wideband beacons", which you can follow through this [repository](https://github.com/A-Rozmarynowicz/Portfolio_Quadcopter).
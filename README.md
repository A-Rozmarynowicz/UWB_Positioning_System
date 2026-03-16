# UWB Positioning System
An indoor positioning system based on Ultra-Wideband beacons. It allows centimeter-accurate positioning of a moving tag, specifically designed for UAVs.

Created both software and hardware.

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)

## General info
- A communication system consisting of a moving tag and at least four ranging anchors.
- The tag and anchors are based on an DWM1000 ranging module and an ESP32.
- Implemented an algorithm for least square error estimation of the 3D coordinates, based on uncertain distance measurements.
- Designed and built a custom PCB with a 3D printed casing.
- Simulated and visualized the process in MATLAB.
- Created a Doxygen documentation.

## Project structure
The project has been split into two parts: hardware and software, that are available in the [Hardware](/Hardware/) and [Software](/Software/) folders, along with more details on each part.

## Important note
As the project has been developed by me logged into a different account, the majority of commits come from "RocketEquation" and "arozmary" accounts, both of which belong to me.

## Motivation
As I decided on my Bachelor's project (full implementation of a quadcopter) I needed a way to position an UAV in an indoor environment. As I couldn't rely on GPS signal, I decided to create a DIY substitution. I experimented with a few ranging technologies, and finally settled with ultra-wideband beacons.

## Technologies
Programming languages:
- C
- C++

Communication protocols:
- ESP-NOW
- UWB
- SPI
- I2C
- UART

CAD softwares for hardware design:
- Altium Designer
- Autodesk Fusion

## Setup
To run the project, please first refer to the details in [Hardware](/Hardware/) folder, and then follow the instructions in the [Software](/Software/) folder.

## Roadmap

- [x] asd
- [ ] asd

## Author
Arkadiusz Rozmarynowicz.
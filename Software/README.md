# UWB Positioning System - software
This folder contains subprojects associated with the software part of the UWB Positioning System.

## Table of contents
* [General info](#general-info)
* [Project structure](#project-structure)
* [Setup](#setup)
* [Technologies](#technologies)

## General info
- Mitigation of loss of communication.
- The anchors automatically determine their relative position on start-up.
- Implemented an algorithm for least square error estimation of the 3D coordinates, based on uncertain distance measurements.
- Doxygen documentation.

## Project structure
- The [Lighthouse](Lighthouse/) folder contains code that is uploaded to an ESP32 anchor.
- The [Observer](Observer/) folder contains code that is uploaded to an ESP32 tag.
- The [Sailor](Sailor/) folder contains code uploaded to an STM32 module, connected to tag via UART.
- The [Doxygen](Doxygen/) folder contains files related to generating the documentation.

## Setup
To run this project, upload the [Lighthouse](./Lighthouse/) code to an ESP32, connected to a DWM1000 as discussed in the [Hardware](/Hardware/) part. Similarly, upload the [Observer](./Observer/) code to an ESP32 + DWM1000 module. Then follow the setup instructions given in the [Lighthouse](./Lighthouse/) folder.

## Technologies
Programming languages:
- C
- C++

Tools used:
- PlatformIO
- STM32 Cube IDE
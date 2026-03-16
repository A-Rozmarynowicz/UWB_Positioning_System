# UWB Positioning System - software
This folder contains files associated with software of the UWB Positioning System.

## Table of contents


## General info
- Implementation of a UWB anchor, also referred to as a "lighthouse".
- Implementation of a UWB tag, also referred to as an "observer"
-

- Implemented a state machine that:
    - allows the anchors to automatically determine their relative position after power-up
    - mitigates communication issues among the modules
    - enables positioning of the tag only when the anchors are setup properly.

- Additionally, implemented a low-level I2C communication between an STM32 and an LCD.

## Project structure
-

## Pliki
- W folderze [LighthouseESP](LighthouseESP/) znajduje się kod wgrywany do modułów latarnii, ten sam kod dla każdej latarnii.
- W folderze [Observer](Observer/) znajduje się kod wgrywany do mobilnego ESP odpowiadającego za komunikację z latarniami.
- W folderze [Sailor](Sailor/) znajduje się kod wgrywany do STM32 podłączonego do mobilnego ESP, odpowiadającego za wyświetlanie mierzonej pozycji na wyświetlaczu LCD.
- W folderze [MATLAB_Simulations](MATLAB_Simulations/) znajdują się symulacje MATLAB.

## Efekty symulacji
- W folderze [Pictures](Pictures/) znajdują się efekty symulacji z MATLABa

## Setup
To run this project, install it locally using npm:
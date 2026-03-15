# UWB Positioning System
An indoor positioning system based on Ultra-Wideband beacons. It allows centimeter-accurate positioning of a moving tag, specifically designed for UAVs.

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)

## General info
- 

## Motivation
As I decided on my Bachelor's project (full implementation of a quadcopter) I needed a way to position an UAV in an indoor environment. As I couldn't rely on GPS signal, I decided to create a DIY substitution. I experimented with a few ranging technologies, and finally settled with ultra-wideband beacons.

## Technologies
Project is created with:
* Lorem version: 12.3
* Ipsum version: 2.33
* Ament library version: 999

## Setup
To run this project, install it locally using npm:

```
$ cd ../lorem
$ npm install
$ npm start
```


## About the project
Projekt wykonany w ramach przedmiotu PMIK. Umożliwia lokalizację modułu ESP32 za pomocą nadajników UWB. Cztery 'latarnie' umieszczone są w odległości parę metrów od siebie, a jeden z modułów może się poruszać w zasięgu latarni, jednocześnie wyznaczając swoją pozycję względną.

## Autor
Arkadiusz Rozmarynowicz

## Pliki
- W folderze [LighthouseESP](LighthouseESP/) znajduje się kod wgrywany do modułów latarnii, ten sam kod dla każdej latarnii.
- W folderze [Observer](Observer/) znajduje się kod wgrywany do mobilnego ESP odpowiadającego za komunikację z latarniami.
- W folderze [Sailor](Sailor/) znajduje się kod wgrywany do STM32 podłączonego do mobilnego ESP, odpowiadającego za wyświetlanie mierzonej pozycji na wyświetlaczu LCD.
- W folderze [MATLAB_Simulations](MATLAB_Simulations/) znajdują się symulacje MATLAB.

## Efekty symulacji
- W folderze [Pictures](Pictures/) znajdują się efekty symulacji z MATLABa

## Do formularza
W każdym podprojekcie w README znajduje się pomoc w wypełnianiu formularza do oceny.

## Uwaga
W paru przypadkach użyto opóźnień blokujących (delay), jednak każde użycie jest konieczne i mogę je usprawiedliwić.
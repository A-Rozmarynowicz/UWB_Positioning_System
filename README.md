# Lighthouse Positioning System

## O projekcie
Projekt wykonany w ramach przedmiotu PMIK. Umożliwia lokalizację modułu ESP32 za pomocą nadajników UWB. Cztery 'latarnie' umieszczone są w odległości parę metrów od siebie, a jeden z modułów może się poruszać w zasięgu latarni, jednocześnie wyznaczając swoją pozycję względną.

## Autor
Arkadiusz Rozmarynowicz

## Pliki
- W folderze "LighthouseESP" znajduje się kod wgrywany do modułów latarnii, ten sam kod dla każdej latarnii.
- W folderze "Observer" znajduje się kod wgrywany do mobilnego ESP odpowiadającego za komunikację z latarniami.
- W folderze "Sailor" znajduje się kod wgrywany do STM32 podłączonego do mobilnego ESP, odpowiadającego za wyświetlanie mierzonej pozycji na wyświetlaczu LCD.
- W folderze "MATLAB_Simulations" znajdują się symulacje MATLAB.

## Do formularza
W każdym podprojekcie w README znajduje się pomoc w wypełnianiu formularza do oceny.

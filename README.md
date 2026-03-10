# Lighthouse Positioning System

## O projekcie
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
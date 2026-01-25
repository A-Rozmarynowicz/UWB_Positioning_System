# Sailor
Kod wgrywany do modułu STM32.

## Opis logiki
Program po otrzymaniu informacji o pozycji wyświetla ją na ekranie LCD. Obsługę LCD zaimplementowano bez użycia biblioteki.

## Hardware
STM32 podłączone do ESP32 poprzez UART, oraz do LCD poprzez I2C.

## Do formularza:
- struktury: tak
- timery: tak
- DMA: tak
- przerwania: tak, od timera, od DMA
- delay: brak
- możliwość wykorzystania kodu w innym projekcie: tak, praktycznie stworzono bibliotekę do obsługi LCD.

## Link do głównej dokumentacji:
* - [Dokumentacja](../../../../Doxygen/output/html/index.html)
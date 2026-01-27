# Observer
Kod wgrywany do mobilnego modułu ESP32.

## Opis logiki
Działaniem programu zarządza automat stanów. Po otrzymaniu informacji o końcu konfiguracji latarni, moduł wysyła zapytania do każdej latarni o jej pozycję. Następnie przechodzi do pomiaru odległości i obliczania pozycji.

## Hardware
ESP32 podłączone do DWM1000 poprzez SPI, oraz do STM32 poprzez UART.

## Do formularza:
- struktury: tak, parę

- timery: tak, jeden
- przerwania: tak, od timera, od ESP-NOW, od DWM1000
- delay: tylko tam gdzie to naprawdę konieczne (restart DWM1000)
- możliwość wykorzystania kodu w innym projekcie: tak, są oddzielne pliki do obliczania pozycji, do automatu stanów, do timerów itp.

## Uwaga
- Czasem wyskakuje pewien warning: pochodzi on z gotowej biblioteki, nie z mojego kodu.

## Link do głównej dokumentacji:
* - [Dokumentacja](../../../../Doxygen/output/html/index.html)
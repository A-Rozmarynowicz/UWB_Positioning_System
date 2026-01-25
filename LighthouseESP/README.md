# LighthouseESP
Kod wgrywany do modułów 'latarni'.

## Opis logiki
Działaniem programu zarządza automat stanów. Początkowo latarnie wyznaczają wzajemne odległości. Następnie jedna z nich zbiera informacje o pomiarach i oblicza względne pozycje. Na koniec wysyła informacje o sukcesie do modułu 'Observer'.

## Hardware
ESP32 podłączone do DWM1000 poprzez SPI.

## Do formularza:
- struktury: tak, kilka

- timery: tak, dwa
- przerwania: tak, od timerów, od ESP-NOW, od DWM1000
- delay: tylko tam gdzie to naprawdę konieczne (restart DWM1000)
- możliwość wykorzystania kodu w innym projekcie: tak, są oddzielne pliki do obliczania pozycji, do automatu stanów, do timerów itp.
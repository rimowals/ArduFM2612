Firmware ARDU2612
=================

Opis
----
Firmware steruje układem YM2612 i mapuje komunikaty MIDI na rejestry syntezatora.
Główny plik: ARDU2612.ino

Pliki
-----
- ARDU2612.ino  -> główna aplikacja
- YM2612.h/.cpp -> warstwa sterownika układu FM
- instr.h       -> patche/instrumenty (VGI)
- VGI.h         -> definicje struktur patchy
- LinkedList.h  -> pomocnicze struktury danych

Wymagania
---------
- Arduino IDE 1.8.x+ lub 2.x
- Biblioteka MIDI (FortySevenEffects)
- Płytka z ATmega328P, 16 MHz

Szybka kompilacja
-----------------
1. Otwórz ARDU2612.ino
2. Zainstaluj bibliotekę "MIDI Library" (autor: FortySevenEffects)
3. Wybierz port i płytkę ATmega328P
4. Wgraj firmware

Obsługa MIDI
------------
- Note On / Note Off
- Pitch Bend
- Control Change (parametry YM2612)

Notatki
-------
- W kodzie jest transpozycja pitch +36 (zależnie od projektu).
- Jeżeli brzmienie jest za wysokie/za niskie, zacznij diagnostykę od tej wartości.
- Jeżeli nie ma dźwięku, najpierw sprawdź linię danych D0..D7 oraz sygnały CS/WR/RD/A0/A1.

Ardu2812 — README (PL/EN)

PL:
Open-source projekt DIY syntezatora FM (YM2812/OPLL).
Repo zawiera Firmware, Board i Gerber.
Licencje:
- Software: MIT (LICENSE-SOFTWARE-MIT.txt)
- Hardware: CERN-OHL-P-2.0 (LICENSE-HARDWARE-CERN-OHL-P-2.0.txt)

EN:
Open-source DIY FM synth project (YM2812/OPLL).
Repository includes Firmware, Board, and Gerber files.
Licenses:
- Software: MIT (LICENSE-SOFTWARE-MIT.txt)
- Hardware: CERN-OHL-P-2.0 (LICENSE-HARDWARE-CERN-OHL-P-2.0.txt)


ARDU2612 / ArduFM
=================

Publiczne repozytorium projektu syntezatora FM opartego o układ YM2612
sterowany przez ATmega328P (Arduino).

Status projektu
---------------
- Projekt hobbystyczny / makerski
- Zawiera: hardware + firmware + pliki produkcyjne PCB
- Repo przygotowane do publikacji i dalszego forka

Struktura repozytorium
----------------------
- Board/      -> projekt KiCad (schemat + PCB) + BOM
- Gerber/     -> gotowe pliki produkcyjne (Gerber + wiercenia)
- Firmware/   -> kod Arduino/C++ sterujący YM2612
- Pics/       -> zdjęcia, rendery, zrzuty schematu
- Doc/        -> materiały pomocnicze

Co robi projekt
---------------
- Odbiera komunikaty MIDI i odtwarza dźwięk przez YM2612
- Obsługuje Note On/Off, Pitch Bend oraz Control Change
- Umożliwia ładowanie patchy (voice) oraz parametryzację brzmienia

Wymagania (skrót)
-----------------
- MCU: ATmega328P @ 16 MHz
- FM IC: YM2612
- Biblioteki Arduino: MIDI
- Zasilanie i tor audio zgodnie ze schematem (Board/)

Szybki start
------------
1) Hardware:
   - Otwórz Board/ArduFM.kicad_pro
   - Sprawdź listę elementów: Board/bom.txt
   - Zamów PCB z folderu Gerber/ lub wygeneruj własne

2) Firmware:
   - Otwórz Firmware/ARDU2612.ino w Arduino IDE
   - Zainstaluj bibliotekę MIDI (FortySevenEffects)
   - Wybierz płytkę zgodną z ATmega328P i wgraj program

3) Test:
   - Podłącz MIDI IN
   - Podłącz wyjście audio
   - Wyślij nuty z klawiatury / DAW

Mapowanie kontrolerów MIDI (CC)
-------------------------------
Przykładowo w kodzie zaimplementowano m.in.:
- CC1   -> LFO / mod wheel
- CC14  -> Feedback
- CC15  -> AMS
- CC16  -> FMS
- CC17  -> Algorithm
- CC18  -> Stereo
(pełna mapa: Firmware/ARDU2612.ino)

Uwagi techniczne
----------------
- To nie jest „drop-in” shield do Arduino UNO — to dedykowana płytka.
- Przed uruchomieniem koniecznie zweryfikuj polaryzację elektrolitów,
  zasilanie i poziomy logiczne.
- Dla stabilnej pracy audio zalecane jest prowadzenie mas zgodnie ze schematem
  i trzymanie się elementów z BOM.


Autor
-----
Sławomir Cichoń (Slav)

Miłego lutowania i niech FM będzie z Tobą.

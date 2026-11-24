# Firmware

**PL:** Firmware dla ATmega328P (Arduino Uno/Nano). Odbiera MIDI i zapisuje rejestry YM2612.

- `ARDU2612.ino` – obsługa MIDI i mapa CC
- `YM2612.h/.cpp` – sterownik układu i przydział głosów
- `instr.h` – 48 brzmień (VGI), `VGI.h` – format brzmienia

Kompilacja: Arduino IDE + biblioteka MIDI Library (FortySevenEffects), płytka z ATmega328P 16 MHz. Jest też projekt Visual Studio + Visual Micro.

Brak dźwięku? Sprawdź zegar YM na pinie D9 (8 MHz), potem linie D0–D7, CS, WR, A0, A1 i IC.

**EN:** Firmware for the ATmega328P (Arduino Uno/Nano). It reads MIDI and writes YM2612 registers.

- `ARDU2612.ino` – MIDI handling and the CC map
- `YM2612.h/.cpp` – chip driver and voice allocation
- `instr.h` – 48 patches (VGI), `VGI.h` – patch format

Build: Arduino IDE + MIDI Library (FortySevenEffects), an ATmega328P board at 16 MHz. A Visual Studio + Visual Micro project is included too.

No sound? Check the YM clock on pin D9 (8 MHz) first, then D0–D7, CS, WR, A0, A1 and IC.

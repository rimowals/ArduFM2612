# Ardu2812

PL 🇵🇱 | EN 🇬🇧

---

## PL: Opis projektu

Open-source projekt DIY syntezatora FM opartego o układ **YM2812 (OPLL)** z mikrokontrolerem.  
Repozytorium zawiera komplet plików do odtworzenia projektu: firmware, PCB oraz pliki produkcyjne.

### Co znajdziesz w repo
- `Firmware/` – kod źródłowy i pliki do kompilacji firmware
- `Board/` – projekt płytki PCB
- `Gerber/` – gotowe pliki produkcyjne do zamówienia PCB
- `readme.txt` – skrócony opis (wersja tekstowa)
- `README.md` – wersja rozszerzona (PL/EN)

### Funkcje (high-level)
- generowanie dźwięku FM/OPLL na YM2812
- sterowanie z mikrokontrolera (logika instrumentu / presetów)
- hardware gotowy do samodzielnego montażu i modyfikacji

> Uwaga: jeśli hardware/forki różnią się wersją układu lub pinoutem, sprawdź zgodność przed programowaniem.

### Szybki start
1. Zamów PCB z katalogu `Gerber/`
2. Skompletuj BOM zgodnie ze schematem w `Board/`
3. Polutuj układ i sprawdź zasilanie przed pierwszym uruchomieniem
4. Otwórz projekt firmware z `Firmware/`, ustaw target i wgraj wsad
5. Przetestuj audio, inicjalizację YM2812 i reakcję na sterowanie

### Licencje
Projekt udostępniony „do dowolnego wykorzystania” (również komercyjnego), z zachowaniem informacji licencyjnych:

- **Software:** MIT (`LICENSE-SOFTWARE-MIT.txt`)
- **Hardware:** CERN-OHL-P-2.0 (`LICENSE-HARDWARE-CERN-OHL-P-2.0.txt`)

---

## EN: Project overview

Open-source DIY FM synthesizer project based on **YM2812 (OPLL)** and a microcontroller.  
This repository includes everything needed to reproduce the project: firmware, PCB design, and production files.

### Repository contents
- `Firmware/` – source code and firmware build files
- `Board/` – PCB design files
- `Gerber/` – manufacturing files ready for PCB fab
- `readme.txt` – short text version
- `README.md` – extended bilingual version (PL/EN)

### Features (high-level)
- FM/OPLL sound generation on YM2812
- microcontroller-based control logic (instrument/presets)
- hardware designed for DIY assembly and modifications

> Note: if your hardware/fork differs in chip version or pinout, verify compatibility before flashing.

### Quick start
1. Order PCB using files in `Gerber/`
2. Assemble BOM according to `Board/` schematics
3. Solder and validate power rails before first power-on
4. Open firmware project from `Firmware/`, set target and flash
5. Test audio output, YM2812 initialization, and control response

### Licenses
The project is provided for broad use (including commercial), while keeping license notices:

- **Software:** MIT (`LICENSE-SOFTWARE-MIT.txt`)
- **Hardware:** CERN-OHL-P-2.0 (`LICENSE-HARDWARE-CERN-OHL-P-2.0.txt`)

---

## Project tree

```text
Ardu2812/
├─ Board/
│  ├─ readme.txt
│  └─ README.md
├─ Firmware/
│  ├─ readme.txt
│  └─ README.md
├─ Gerber/
│  ├─ readme.txt
│  └─ README.md
├─ LICENSE-SOFTWARE-MIT.txt
├─ LICENSE-HARDWARE-CERN-OHL-P-2.0.txt
├─ LICENSE-README.txt
├─ readme.txt
└─ README.md
```

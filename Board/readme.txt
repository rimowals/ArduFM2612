Board (KiCad)
=============

Zawartość
---------
- ArduFM.kicad_pro -> projekt główny
- ArduFM.kicad_sch -> schemat
- ArduFM.kicad_pcb -> PCB
- bom.txt          -> lista elementów

Wskazówki montażowe
-------------------
- Zacznij od elementów niskich (rezystory, diody), potem podstawki/układy,
  na końcu elektrolity i złącza.
- Sprawdź orientację:
  - diody (1N4004, 1N4148),
  - LED,
  - elektrolity,
  - układy DIP (pin 1),
  - stabilizatory 78xx.
- Po montażu wykonaj testy sekcji zasilania bez włożonych drogich układów.

BOM
---
Oficjalna lista części znajduje się w pliku bom.txt.

Produkcja PCB
-------------
Do zamówienia płytek użyj folderu Gerber/ z katalogu głównego repo.

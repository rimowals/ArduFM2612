#include <Arduino.h>
// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       ARDU2612.ino
    Created:	05.02.2022 12:13:20
    Author:     SLAV-RYZEN\Sławomir Cichoń
*/

#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

#include "YM2612.h"
#include "instr.h"

YM2612 ym;
#define YM_IC A5
#define YM_CS A4
#define YM_WR A3
#define YM_RD A2
#define YM_A0 A1
#define YM_A1 A0
#define YM_MC 9
#define YM_D0 10
#define YM_D1 11
#define YM_D2 2
#define YM_D3 3
#define YM_D4 4
#define YM_D5 5
#define YM_D6 6
#define YM_D7 7

byte play_seq = 0;
uint16_t currentVoice = 0;

VGI_t getSomeVoice() {
    VGI_t cv;
    cv.Algorithm = 7;
    cv.Feedback = 0;
    cv.AMD_FMD = 0;

    cv.ops[0].Attack_Rate = 31;
    cv.ops[0].Decay_Rate_AM_enable = 23;
    cv.ops[0].Sustain_Rate = 22;
    cv.ops[0].Release_Rate = 8;
    cv.ops[0].Total_Level = 0;
    cv.ops[0].Sustain_Level = 0;
    cv.ops[0].Multiplier = 4;
    cv.ops[0].Detune = 0;
    cv.ops[0].Rate_Scaling = 0;
    cv.ops[0].SSG_EG = 0;

    cv.ops[1].Attack_Rate = 31;
    cv.ops[1].Decay_Rate_AM_enable = 22;
    cv.ops[1].Sustain_Rate = 20;
    cv.ops[1].Release_Rate = 8;
    cv.ops[1].Total_Level = 0;
    cv.ops[1].Sustain_Level = 4;
    cv.ops[1].Multiplier = 1;
    cv.ops[1].Detune = 0;
    cv.ops[1].Rate_Scaling = 0;
    cv.ops[1].SSG_EG = 0;

    cv.ops[2].Attack_Rate = 31;
    cv.ops[2].Decay_Rate_AM_enable = 20;
    cv.ops[2].Sustain_Rate = 17;
    cv.ops[2].Release_Rate = 8;
    cv.ops[2].Total_Level = 0;
    cv.ops[2].Sustain_Level = 4;
    cv.ops[2].Multiplier = 2;
    cv.ops[2].Detune = 0;
    cv.ops[2].Rate_Scaling = 0;
    cv.ops[2].SSG_EG = 0;

    cv.ops[3].Attack_Rate = 31;
    cv.ops[3].Decay_Rate_AM_enable = 20;
    cv.ops[3].Sustain_Rate = 17;
    cv.ops[3].Release_Rate = 8;
    cv.ops[3].Total_Level = 0;
    cv.ops[3].Sustain_Level = 4;
    cv.ops[3].Multiplier = 3;
    cv.ops[3].Detune = 0;
    cv.ops[3].Rate_Scaling = 0;
    cv.ops[3].SSG_EG = 0;

    return cv;
}

void printSerial3posByte(byte value) {
    if (value < 100) Serial.print(" ");
    if (value < 10) Serial.print(" ");
    Serial.print(value);
}

void printSerial3posByteEndingSpace(byte value) {
    printSerial3posByte(value);
    Serial.print(" ");
}

void printVoice(VGI_t v) {
    Serial.println("--------------------------------");
    Serial.println(String((char*)v.Name));
    Serial.println("--------------------------------");
    Serial.println("ALG AMS FMS  FB");
    printSerial3posByteEndingSpace(v.Algorithm);
    printSerial3posByteEndingSpace((v.AMD_FMD & 0xF0) >> 4);
    printSerial3posByteEndingSpace(v.AMD_FMD & 0x0F);
    printSerial3posByteEndingSpace(v.Feedback); Serial.println(" ");
    Serial.println("[OP]  AR  DR  SR  RR  TL  SL  MUL DT  RS  EG");
    Serial.print(" [0] ");
    printSerial3posByteEndingSpace(v.ops[0].Attack_Rate);
    printSerial3posByteEndingSpace(v.ops[0].Decay_Rate_AM_enable);
    printSerial3posByteEndingSpace(v.ops[0].Sustain_Rate);
    printSerial3posByteEndingSpace(v.ops[0].Release_Rate);
    printSerial3posByteEndingSpace(v.ops[0].Total_Level);
    printSerial3posByteEndingSpace(v.ops[0].Sustain_Level);
    printSerial3posByteEndingSpace(v.ops[0].Multiplier);
    printSerial3posByteEndingSpace(v.ops[0].Detune);
    printSerial3posByteEndingSpace(v.ops[0].Rate_Scaling);
    printSerial3posByteEndingSpace(v.ops[0].SSG_EG);; Serial.println(" ");
    Serial.print(" [1] ");
    printSerial3posByteEndingSpace(v.ops[1].Attack_Rate);
    printSerial3posByteEndingSpace(v.ops[1].Decay_Rate_AM_enable);
    printSerial3posByteEndingSpace(v.ops[1].Sustain_Rate);
    printSerial3posByteEndingSpace(v.ops[1].Release_Rate);
    printSerial3posByteEndingSpace(v.ops[1].Total_Level);
    printSerial3posByteEndingSpace(v.ops[1].Sustain_Level);
    printSerial3posByteEndingSpace(v.ops[1].Multiplier);
    printSerial3posByteEndingSpace(v.ops[1].Detune);
    printSerial3posByteEndingSpace(v.ops[1].Rate_Scaling);
    printSerial3posByteEndingSpace(v.ops[1].SSG_EG);; Serial.println(" ");
    Serial.print(" [2] ");
    printSerial3posByteEndingSpace(v.ops[2].Attack_Rate);
    printSerial3posByteEndingSpace(v.ops[2].Decay_Rate_AM_enable);
    printSerial3posByteEndingSpace(v.ops[2].Sustain_Rate);
    printSerial3posByteEndingSpace(v.ops[2].Release_Rate);
    printSerial3posByteEndingSpace(v.ops[2].Total_Level);
    printSerial3posByteEndingSpace(v.ops[2].Sustain_Level);
    printSerial3posByteEndingSpace(v.ops[2].Multiplier);
    printSerial3posByteEndingSpace(v.ops[2].Detune);
    printSerial3posByteEndingSpace(v.ops[2].Rate_Scaling);
    printSerial3posByteEndingSpace(v.ops[2].SSG_EG);; Serial.println(" ");
    Serial.print(" [3] ");
    printSerial3posByteEndingSpace(v.ops[3].Attack_Rate);
    printSerial3posByteEndingSpace(v.ops[3].Decay_Rate_AM_enable);
    printSerial3posByteEndingSpace(v.ops[3].Sustain_Rate);
    printSerial3posByteEndingSpace(v.ops[3].Release_Rate);
    printSerial3posByteEndingSpace(v.ops[3].Total_Level);
    printSerial3posByteEndingSpace(v.ops[3].Sustain_Level);
    printSerial3posByteEndingSpace(v.ops[3].Multiplier);
    printSerial3posByteEndingSpace(v.ops[3].Detune);
    printSerial3posByteEndingSpace(v.ops[3].Rate_Scaling);
    printSerial3posByteEndingSpace(v.ops[3].SSG_EG); Serial.println("\r\n--------------------------------");;
}

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
    digitalWrite(LED_BUILTIN, HIGH);
    ym.noteOn(channel, pitch + 36, velocity);
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
    digitalWrite(LED_BUILTIN, LOW);
    ym.noteOff(channel, pitch + 36, velocity);
}

void handlePitchBend(byte channel, int bend)
{
    ym.pitchBend(channel, bend);
}

void loadPrevVoice() {
    if (currentVoice > 0) {
        currentVoice--;
    }
    else {
        currentVoice = voicepatch_count - 1;
    }
    ym.loadVgi(getVoicepatch(currentVoice));
}

void loadNextVoice() {
    currentVoice++;
    if (currentVoice >= voicepatch_count)
        currentVoice = 0;
    ym.loadVgi(getVoicepatch(currentVoice));
    return;

}

void handleControlChange(byte channel, byte number, byte value)
{
    if (value == 0 && (number == 112 || number == 113))
        return;

    UNUSED(channel);
    Serial.print(number);

    switch (number) {
        // mod wheel
    case 1:
        ym.setLFO(value);        
        break;
    case 14:
        ym.setFeedback(value);
        break;
    case 15:
        ym.setAMS(value);
        break;
    case 16:
        ym.setFMS(value);
        break;
    case 17:
        ym.setAlgorithm(value);
        break;
    case 18:
        if (value == 0) ym.setStereo(1);
        if (value == 1) ym.setStereo(3);
        if (value == 2) ym.setStereo(2);
        break;
    case 20:
        ym.selectOperator(0, 1);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setAttackRate(value);
        break;
    case 21:
        ym.selectOperator(0, 1);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setDecayRate(value);
        break;
    case 22:
        ym.selectOperator(0, 1);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setSustainRate(value);
        break;
    case 23:
        ym.selectOperator(0, 1);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setReleaseRate(value);
        break;
    case 24:
        ym.selectOperator(0, 1);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setTotalLevel(value);
        break;
    case 25:
        ym.selectOperator(0, 1);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setSustainLevel(value);
        break;
    case 26:
        ym.selectOperator(0, 1);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setMultiply(value);
        break;
    case 27:
        ym.selectOperator(0, 1);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setDetune(value);
        break;
    case 28:
        ym.selectOperator(0, 1);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setRateScaling(value);
        break;
    case 29:
        ym.selectOperator(0, 1);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setSSG_EG(value);
        break;
    case 30:
        ym.selectOperator(0, 1);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setAmplitudeModulation(value);
        break;
    case 40:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 1);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setAttackRate(value);
        break;
    case 41:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 1);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setDecayRate(value);
        break;
    case 42:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 1);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setSustainRate(value);
        break;
    case 43:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 1);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setReleaseRate(value);
        break;
    case 44:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 1);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setTotalLevel(value);
        break;
    case 45:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 1);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setSustainLevel(value);
        break;
    case 46:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 1);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setMultiply(value);
        break;
    case 47:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 1);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setDetune(value);
        break;
    case 48:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 1);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setRateScaling(value);
        break;
    case 49:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 1);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setSSG_EG(value);
        break;
    case 50:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 1);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 0);
        ym.setAmplitudeModulation(value);
        break;
    case 60:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 1);
        ym.selectOperator(3, 0);
        ym.setAttackRate(value);
        break;
    case 61:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 1);
        ym.selectOperator(3, 0);
        ym.setDecayRate(value);
        break;
    case 62:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 1);
        ym.selectOperator(3, 0);
        ym.setSustainRate(value);
        break;
    case 63:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 1);
        ym.selectOperator(3, 0);
        ym.setReleaseRate(value);
        break;
    case 64:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 1);
        ym.selectOperator(3, 0);
        ym.setTotalLevel(value);
        break;
    case 65:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 1);
        ym.selectOperator(3, 0);
        ym.setSustainLevel(value);
        break;
    case 66:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 1);
        ym.selectOperator(3, 0);
        ym.setMultiply(value);
        break;
    case 67:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 1);
        ym.selectOperator(3, 0);
        ym.setDetune(value);
        break;
    case 68:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 1);
        ym.selectOperator(3, 0);
        ym.setRateScaling(value);
        break;
    case 69:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 1);
        ym.selectOperator(3, 0);
        ym.setSSG_EG(value);
        break;
    case 70:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 1);
        ym.selectOperator(3, 0);
        ym.setAmplitudeModulation(value);
        break;
    case 80:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 1);
        ym.setAttackRate(value);
        break;
    case 81:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 1);
        ym.setDecayRate(value);
        break;
    case 82:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 1);
        ym.setSustainRate(value);
        break;
    case 83:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 1);
        ym.setReleaseRate(value);
        break;
    case 84:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 1);
        ym.setTotalLevel(value);
        break;
    case 85:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 1);
        ym.setSustainLevel(value);
        break;
    case 86:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 1);
        ym.setMultiply(value);
        break;
    case 87:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 1);
        ym.setDetune(value);
        break;
    case 88:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 1);
        ym.setRateScaling(value);
        break;
    case 89:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 1);
        ym.setSSG_EG(value);
        break;
    case 90:
        ym.selectOperator(0, 0);
        ym.selectOperator(1, 0);
        ym.selectOperator(2, 0);
        ym.selectOperator(3, 1);
        ym.setAmplitudeModulation(value);
        break;
    
    case 112:
        loadPrevVoice();
        break;
    case 113:
        loadNextVoice();
        break;
    case 117:
        ym.reset();
        break;
    case 119:
        break;
    }
}

int plyCnt = 0;
void playSeq() {
    static uint8_t note = 0;
    static uint32_t previousMillis = 0;
    static uint32_t interval = 400;
    static bool pressed = false;
    uint32_t currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        if (pressed) {
            handleNoteOff(1, 24 + note, 0);
            handleNoteOff(2, 24 + note + 4, 0);
            plyCnt++;
            note++;
            note %= 12;
            pressed = false;
            if (play_seq > 1) {
                play_seq = 0;
            }

        }
        else {
            handleNoteOn(1, 24 + note, 100);
            handleNoteOn(2, 24 + note + 4, 100);
            pressed = true;
        }
    }
}


void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    ym.setup(YM_IC, YM_CS, YM_WR, YM_RD, YM_A0, YM_A1, YM_MC, YM_D0, YM_D1, YM_D2, YM_D3, YM_D4, YM_D5, YM_D6, YM_D7);

    ym.initialize();

    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    MIDI.setHandleControlChange(handleControlChange);
    MIDI.setHandlePitchBend(handlePitchBend);
    MIDI.begin(MIDI_CHANNEL_OMNI);    
    ym.reset();
    getSomeVoice();
    
}

// Add the main program code into the continuous loop() function
void loop()
{
    MIDI.read();
    ym.update();

    if (play_seq > 0)      playSeq();
}

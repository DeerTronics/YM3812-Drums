#include "YM3812.h"

const byte DRUMINS_CLAP2[12]     = { 0x00, 0x3E, 0x00, 0x9F, 0x0F, 0x0F, 0x00, 0x30, 0x00, 0x87, 0xFA, 0x00 };
const byte DRUMINS_SCRATCH1[12]  = { 0x00, 0x01, 0x00, 0x78, 0x97, 0x09, 0x00, 0x02, 0x00, 0x88, 0x98, 0x03 };
const byte DRUMINS_SCRATCH2[12]  = { 0x00, 0x01, 0x00, 0x78, 0x97, 0x09, 0x00, 0x02, 0x00, 0x88, 0x98, 0x03 };
const byte DRUMINS_RIMSHOT2[12]  = { 0x00, 0x16, 0x08, 0xF1, 0xFB, 0x01, 0x00, 0x11, 0x00, 0xF9, 0x69, 0x00 };
const byte DRUMINS_HIQ[12]       = { 0x00, 0x00, 0x00, 0xF8, 0x6C, 0x01, 0x00, 0x0E, 0x80, 0xE8, 0x4A, 0x00 };
const byte DRUMINS_WOODBLOK[12]  = { 0x00, 0x25, 0x1B, 0xFA, 0xF2, 0x01, 0x00, 0x12, 0x00, 0xF6, 0x9A, 0x00 };
const byte DRUMINS_GLOCK[12]     = { 0x00, 0x06, 0x03, 0xF4, 0x44, 0x00, 0x01, 0x01, 0x1B, 0xF2, 0x34, 0x00 };
const byte DRUMINS_BASS_DR2[12]  = { 0x06, 0x00, 0x00, 0xF9, 0xF3, 0x05, 0x00, 0x01, 0x00, 0xF7, 0x8A, 0x00 };
const byte DRUMINS_BASS_DR1[12]  = { 0x06, 0x01, 0x07, 0xFA, 0xFD, 0x05, 0x00, 0x01, 0x00, 0xF6, 0x47, 0x00 };
const byte DRUMINS_RIMSHOT[12]   = { 0x00, 0x16, 0x08, 0xF1, 0xFB, 0x01, 0x00, 0x11, 0x00, 0xF9, 0x69, 0x00 };
const byte DRUMINS_SNARE_AC[12]  = { 0x00, 0x24, 0x00, 0xFF, 0x0F, 0x0F, 0x00, 0x02, 0x00, 0xF7, 0xA9, 0x00 };
const byte DRUMINS_CLAP[12]      = { 0x00, 0x3E, 0x00, 0x9F, 0x0F, 0x0F, 0x00, 0x30, 0x00, 0x87, 0xFA, 0x00 };
const byte DRUMINS_SNARE_EL[12]  = { 0x00, 0x24, 0x00, 0xFF, 0x0F, 0x0F, 0x00, 0x02, 0x00, 0xF7, 0xA9, 0x00 };
const byte DRUMINS_LO_TOMS[12]   = { 0x00, 0x06, 0x0A, 0xFA, 0x1F, 0x0C, 0x00, 0x11, 0x00, 0xF5, 0xF5, 0x00 };
const byte DRUMINS_HIHAT_CL[12]  = { 0x00, 0x2C, 0x00, 0xF2, 0xFE, 0x07, 0x00, 0x02, 0x06, 0xB8, 0xD8, 0x03 };
const byte DRUMINS_HI_TOMS[12]   = { 0x00, 0x06, 0x0A, 0xFA, 0x1F, 0x0C, 0x00, 0x11, 0x00, 0xF5, 0xF5, 0x00 };
const byte DRUMINS_HIHAT_PL[12]  = { 0x00, 0x2C, 0x00, 0xF2, 0xFE, 0x07, 0x00, 0x02, 0x06, 0xB8, 0xD8, 0x03 };
const byte DRUMINS_LOW_TOM[12]   = { 0x00, 0x06, 0x0A, 0xFA, 0x1F, 0x0C, 0x00, 0x11, 0x00, 0xF5, 0xF5, 0x00 };
const byte DRUMINS_HIHAT_OP[12]  = { 0x00, 0x2E, 0x00, 0x82, 0xF6, 0x05, 0x00, 0x04, 0x10, 0x74, 0xF8, 0x03 };
const byte DRUMINS_LTOM_MID[12]  = { 0x00, 0x06, 0x0A, 0xFA, 0x1F, 0x0C, 0x00, 0x11, 0x00, 0xF5, 0xF5, 0x00 };
const byte DRUMINS_HTOM_MID[12]  = { 0x00, 0x06, 0x0A, 0xFA, 0x1F, 0x0C, 0x00, 0x11, 0x00, 0xF5, 0xF5, 0x00 };
const byte DRUMINS_CRASH[12]     = { 0x00, 0x2C, 0x00, 0x9F, 0x0F, 0x0F, 0x02, 0x0E, 0x05, 0xC5, 0xD4, 0x03 };
const byte DRUMINS_TOM_HIGH[12]  = { 0x00, 0x06, 0x0A, 0xFA, 0x1F, 0x0C, 0x00, 0x11, 0x00, 0xF5, 0xF5, 0x00 };
const byte DRUMINS_RIDE_CY[12]   = { 0x00, 0x29, 0x10, 0x94, 0x0F, 0x0F, 0x00, 0x04, 0x04, 0xF9, 0x44, 0x03 };
const byte DRUMINS_TAMBOUR[12]   = { 0x00, 0x2C, 0x00, 0x9F, 0x0F, 0x0F, 0x02, 0x0E, 0x05, 0xC5, 0xD4, 0x03 };
const byte DRUMINS_CYMBAL[12]    = { 0x00, 0x29, 0x10, 0x94, 0x0F, 0x0F, 0x00, 0x04, 0x04, 0xF9, 0x44, 0x03 };
const byte DRUMINS_TAMBOU2[12]   = { 0x00, 0x2E, 0x09, 0xF5, 0xF1, 0x01, 0x00, 0x06, 0x03, 0x87, 0xF7, 0x03 };
const byte DRUMINS_SPLASH[12]    = { 0x00, 0x2C, 0x00, 0x9F, 0x0F, 0x0F, 0x02, 0x0E, 0x05, 0xC5, 0xD4, 0x03 };
const byte DRUMINS_COWBELL[12]   = { 0x00, 0x37, 0x14, 0xF7, 0xA1, 0x09, 0x01, 0x03, 0x00, 0xF6, 0x28, 0x00 };
const byte DRUMINS_CRASH2[12]    = { 0x00, 0x2C, 0x00, 0x9F, 0x0F, 0x0F, 0x02, 0x0E, 0x05, 0xC5, 0xD4, 0x03 };
const byte DRUMINS_VIBRASLA[12]  = { 0x00, 0x80, 0x00, 0xFF, 0x0F, 0x0D, 0x01, 0x00, 0x00, 0xF5, 0xF7, 0x01 };
const byte DRUMINS_RIDE2[12]     = { 0x00, 0x29, 0x10, 0x94, 0x0F, 0x0F, 0x00, 0x04, 0x04, 0xF9, 0x44, 0x03 };
const byte DRUMINS_HI_BONGO[12]  = { 0x00, 0x25, 0xC4, 0xFA, 0xFA, 0x01, 0x00, 0x03, 0x00, 0x99, 0xF9, 0x00 };
const byte DRUMINS_LO_BONGO[12]  = { 0x00, 0x21, 0x03, 0xFB, 0xFA, 0x01, 0x01, 0x02, 0x00, 0xA8, 0xF7, 0x00 };
const byte DRUMINS_MUTECONG[12]  = { 0x00, 0x25, 0xC4, 0xFA, 0xFA, 0x01, 0x00, 0x03, 0x00, 0x99, 0xF9, 0x00 };
const byte DRUMINS_OPENCONG[12]  = { 0x00, 0x24, 0x18, 0xF9, 0xFA, 0x0F, 0x02, 0x03, 0x00, 0xA6, 0xF6, 0x00 };
const byte DRUMINS_LOWCONGA[12]  = { 0x00, 0x24, 0x18, 0xF9, 0xFA, 0x0F, 0x02, 0x03, 0x00, 0xA6, 0xF6, 0x00 };
const byte DRUMINS_HI_TIMBA[12]  = { 0x00, 0x05, 0x14, 0xF5, 0xF5, 0x07, 0x02, 0x03, 0x00, 0xF6, 0x36, 0x02 };
const byte DRUMINS_LO_TIMBA[12]  = { 0x00, 0x05, 0x14, 0xF5, 0xF5, 0x07, 0x02, 0x03, 0x00, 0xF6, 0x36, 0x02 };
const byte DRUMINS_HI_AGOGO[12]  = { 0x00, 0x1C, 0x0C, 0xF9, 0x31, 0x0F, 0x01, 0x15, 0x00, 0x96, 0xE8, 0x01 };
const byte DRUMINS_LO_AGOGO[12]  = { 0x00, 0x1C, 0x0C, 0xF9, 0x31, 0x0F, 0x01, 0x15, 0x00, 0x96, 0xE8, 0x01 };
const byte DRUMINS_CABASA[12]    = { 0x00, 0x0E, 0x00, 0xFF, 0x01, 0x0F, 0x00, 0x0E, 0x02, 0x79, 0x77, 0x03 };
const byte DRUMINS_MARACAS[12]   = { 0x00, 0x0E, 0x00, 0xFF, 0x01, 0x0F, 0x00, 0x0E, 0x02, 0x79, 0x77, 0x03 };
const byte DRUMINS_S_WHISTL[12]  = { 0x00, 0x20, 0x15, 0xAF, 0x07, 0x05, 0x01, 0x0E, 0x00, 0xA5, 0x2B, 0x02 };
const byte DRUMINS_L_WHISTL[12]  = { 0x00, 0x20, 0x18, 0xBF, 0x07, 0x01, 0x01, 0x0E, 0x00, 0x93, 0x3B, 0x02 };
const byte DRUMINS_S_GUIRO[12]   = { 0x00, 0x20, 0x00, 0xF0, 0xF7, 0x0B, 0x00, 0x08, 0x01, 0x89, 0x3B, 0x03 };
const byte DRUMINS_L_GUIRO[12]   = { 0x00, 0x20, 0x00, 0xF3, 0xFA, 0x09, 0x00, 0x08, 0x0A, 0x53, 0x2B, 0x02 };
const byte DRUMINS_CLAVES[12]    = { 0x00, 0x15, 0x21, 0xF8, 0x9A, 0x09, 0x01, 0x13, 0x00, 0xF6, 0x89, 0x00 };
const byte DRUMINS_HI_WDBLK[12]  = { 0x00, 0x25, 0x1B, 0xFA, 0xF2, 0x01, 0x00, 0x12, 0x00, 0xF6, 0x9A, 0x00 };
const byte DRUMINS_LO_WDBLK[12]  = { 0x00, 0x25, 0x1B, 0xFA, 0xF2, 0x01, 0x00, 0x12, 0x00, 0xF6, 0x9A, 0x00 };
const byte DRUMINS_MU_CUICA[12]  = { 0x00, 0x20, 0x01, 0x5F, 0x07, 0x01, 0x00, 0x08, 0x00, 0x87, 0x4B, 0x01 };
const byte DRUMINS_OP_CUICA[12]  = { 0x00, 0x25, 0x12, 0x57, 0xF7, 0x01, 0x01, 0x03, 0x00, 0x78, 0x67, 0x01 };
const byte DRUMINS_MU_TRNGL[12]  = { 0x00, 0x22, 0x2F, 0xF1, 0xF0, 0x07, 0x00, 0x27, 0x02, 0xF8, 0xFC, 0x00 };
const byte DRUMINS_OP_TRNGL[12]  = { 0x00, 0x26, 0x44, 0xF1, 0xF0, 0x07, 0x00, 0x27, 0x40, 0xF5, 0xF5, 0x00 };
const byte DRUMINS_SHAKER[12]    = { 0x00, 0x0E, 0x00, 0xFF, 0x01, 0x0F, 0x00, 0x0E, 0x02, 0x79, 0x77, 0x03 };
const byte DRUMINS_TRIANGL1[12]  = { 0x00, 0x26, 0x44, 0xF1, 0xFF, 0x07, 0x00, 0x27, 0x40, 0xF5, 0xF5, 0x00 };
const byte DRUMINS_TRIANGL2[12]  = { 0x00, 0x26, 0x44, 0xF1, 0xFF, 0x07, 0x00, 0x27, 0x40, 0xF5, 0xF5, 0x00 };
const byte DRUMINS_RIMSHOT3[12]  = { 0x00, 0x16, 0x08, 0xF1, 0xFB, 0x01, 0x00, 0x11, 0x00, 0xF9, 0x69, 0x00 };
const byte DRUMINS_RIMSHOT4[12]  = { 0x00, 0x16, 0x08, 0xF1, 0xFB, 0x01, 0x00, 0x11, 0x00, 0xF9, 0x69, 0x00 };
const byte DRUMINS_TAIKO[12]     = { 0x00, 0x02, 0x1D, 0xF5, 0x93, 0x01, 0x00, 0x00, 0x00, 0xC6, 0x45, 0x00 };


const byte INSTRUMENT_ORGAN1[12] = { 0x00, 0xE2, 0x07, 0xF4, 0x1B, 0x06, 0x01, 0xE0, 0x00, 0xF4, 0x0D, 0x01 };

const byte INSTRUMENT_BDRUM1[12] = { 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xA8, 0x4C, 0x00 };
const byte INSTRUMENT_BDRUM2[12] = { 0x06, 0x00, 0x0B, 0xA8, 0x4C, 0x00, 0x00, 0x00, 0x00, 0xA8, 0x4C, 0x00 };
const byte INSTRUMENT_RKSNARE1[12] = { 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0xC8, 0xB6, 0x01 };
const byte INSTRUMENT_TOM2[12] = { 0x08, 0x02, 0x00, 0xC8, 0x97, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const byte INSTRUMENT_CYMBAL1[12] = { 0x09, 0x01, 0x00, 0xF5, 0xB5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const byte INSTRUMENT_HIHAT2[12] = { 0x0A, 0x01, 0x03, 0xDA, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

void setup() {
  setup_ym3812();
  reset_ym3812();

  // Set percussion mode and load instruments.
  setPercussion(true);
  setDrumInstrument(DRUMINS_BASS_DR1);
  //setDrumInstrument(DRUMINS_SNARE_EL);
  //setDrumInstrument(INSTRUMENT_TOM2);
  //setDrumInstrument(DRUMINS_CLAP2);
  //setDrumInstrument(INSTRUMENT_HIHAT2);

  // Set octave and frequency for bass drum.
  //setBlock(6, 2);
  //setFNumber(6, getNoteFNumber(NOTE_C));
  //setRelease(6, OPERATOR1, 8);
  //setRelease(6, OPERATOR2, 8);
  //setVolume(6, OPERATOR1, 0);
  //setVolume(6, OPERATOR2, 0);
  
  //setVolume(7, OPERATOR1, 8);
  //setVolume(7, OPERATOR2, 8);


  // Set octave and frequency for snare drum and hi-hat.
  //setBlock(7, 2);
  //setFNumber(7, getNoteFNumber(NOTE_C));
  // Set low volume on hi-hat
  //setVolume(3, OPERATOR1, 8);

  // Set octave and frequency for tom tom and cymbal.
  //setBlock(8, 3);
  //setFNumber(8, getNoteFNumber(NOTE_A));
  
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
}

int i = 0;
byte gate1_old = 0;
byte gate2_old = 0;
byte gate3_old = 0;
byte gate4_old = 0;
byte gate5_old = 0;
void loop() {
  byte gate1 = !digitalRead(A0);
  byte gate2 = !digitalRead(A1);
  byte gate3 = !digitalRead(A2);
  byte gate4 = !digitalRead(A3);
  byte gate5 = !digitalRead(A4);
  
  bool bass   = false;
  bool snare  = false;
  bool tom    = false;
  bool cymbal = false;
  bool hiHat  = false;

  if (gate1_old == 0 && gate1 == 1) {
    bass = true;
    gate1_old = 1;
  } else if (gate1_old == 1 && gate1 == 0) {
    gate1_old = 0;
  }
  if (gate2_old == 0 && gate2 == 1) {
    snare = true;
    gate2_old = 1;
  } else if (gate2_old == 1 && gate2 == 0) {
    gate2_old = 0;
  }
  if (gate3_old == 0 && gate3 == 1) {
    tom = true;
    gate3_old = 1;
  } else if (gate3_old == 1 && gate3 == 0) {
    gate3_old = 0;
  }
  if (gate4_old == 0 && gate4 == 1) {
    cymbal = true;
    gate4_old = 1;
  } else if (gate4_old == 1 && gate4 == 0) {
    gate4_old = 0;
  }
  if (gate5_old == 0 && gate5 == 1) {
    hiHat = true;
    gate5_old = 1;
  } else if (gate5_old == 1 && gate5 == 0) {
    gate5_old = 0;
  } 

  setDrums(bass, snare, tom, cymbal, hiHat);

  delay(10);
}

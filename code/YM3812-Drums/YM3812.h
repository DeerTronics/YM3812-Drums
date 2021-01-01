/*
  YM3812.h - Library for controlling OPL2 sound chip
  Created by Sebastian Murgul, November 16, 2020.
  Released into the public domain.
*/

#ifndef YM3812_h
#define YM3812_h

#include "Arduino.h"

#define OPL2_NUM_CHANNELS 9
#define CHANNELS_PER_BANK 9

// Operator definitions.
#define OPERATOR1 0
#define OPERATOR2 1
#define MODULATOR 0
#define CARRIER 1

// Synthesis type definitions.
#define SYNTH_MODE_FM 0
#define SYNTH_MODE_AM 1

// Drum sounds.
#define DRUM_BASS 0
#define DRUM_SNARE 1
#define DRUM_TOM 2
#define DRUM_CYMBAL 3
#define DRUM_HI_HAT 4

// Drum sound bit masks.
#define DRUM_BITS_BASS 0x10
#define DRUM_BITS_SNARE 0x08
#define DRUM_BITS_TOM 0x04
#define DRUM_BITS_CYMBAL 0x02
#define DRUM_BITS_HI_HAT 0x01

// Instrument type definitions.
#define INSTRUMENT_TYPE_MELODIC  0
#define INSTRUMENT_TYPE_BASS     6
#define INSTRUMENT_TYPE_SNARE    7
#define INSTRUMENT_TYPE_TOM      8
#define INSTRUMENT_TYPE_CYMBAL   9
#define INSTRUMENT_TYPE_HI_HAT  10

// Note to frequency mapping.
#define NOTE_C 0
#define NOTE_CS 1
#define NOTE_D 2
#define NOTE_DS 3
#define NOTE_E 4
#define NOTE_F 5
#define NOTE_FS 6
#define NOTE_G 7
#define NOTE_GS 8
#define NOTE_A 9
#define NOTE_AS 10
#define NOTE_B 11

// Tune specific declarations.
#define NUM_OCTAVES 7
#define NUM_NOTES 12
#define NUM_DRUM_SOUNDS 5

const float fIntervals[8] = {
    0.048, 0.095, 0.190, 0.379, 0.759, 1.517, 3.034, 6.069};
const unsigned int noteFNumbers[12] = {
    0x156, 0x16B, 0x181, 0x198, 0x1B0, 0x1CA,
    0x1E5, 0x202, 0x220, 0x241, 0x263, 0x287};
const float blockFrequencies[8] = {
    48.503, 97.006, 194.013, 388.026,
    776.053, 1552.107, 3104.215, 6208.431};
const byte registerOffsets[2][9] = {
    {0x00, 0x01, 0x02, 0x08, 0x09, 0x0A, 0x10, 0x11, 0x12}, /*  initializers for operator 1 */
    {0x03, 0x04, 0x05, 0x0B, 0x0C, 0x0D, 0x13, 0x14, 0x15}  /*  initializers for operator 2 */
};
const byte drumRegisterOffsets[2][5] = {
    {0x10, 0xFF, 0x12, 0xFF, 0x11},
    {0x13, 0x14, 0xFF, 0x15, 0xFF}};
const byte drumChannels[5] = {
    6, 7, 8, 8, 7};
const byte drumBits[5] = {
    DRUM_BITS_BASS, DRUM_BITS_SNARE, DRUM_BITS_TOM, DRUM_BITS_CYMBAL, DRUM_BITS_HI_HAT};

int _CS = 12;
int _A0 = 11;
int _IC = 10;

int _dataPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};

byte *chipRegisters = new byte[3];                          //  3
byte *channelRegisters = new byte[3 * OPL2_NUM_CHANNELS];   // 27
byte *operatorRegisters = new byte[10 * OPL2_NUM_CHANNELS]; // 90

void writedatapins_ym3812(unsigned char data) //Digital I/O
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(*(_dataPins + i), ((data >> i) & 1));
  }
}

void senddata_ym3812(unsigned char addr, unsigned char data)
{
  digitalWrite(_CS, HIGH);
  digitalWrite(_A0, LOW);

  writedatapins_ym3812(addr);

  digitalWrite(_CS, LOW);
  delayMicroseconds(16);
  digitalWrite(_CS, HIGH);
  delayMicroseconds(16);

  digitalWrite(_A0, HIGH);

  writedatapins_ym3812(data);

  digitalWrite(_CS, LOW);
  delayMicroseconds(4);
  digitalWrite(_CS, HIGH);
  delayMicroseconds(92);

  digitalWrite(_A0, HIGH);
}

void setup_ym3812()
{
  for (int i = 0; i < 8; i++)
  {
    pinMode(*(_dataPins + i), OUTPUT);
  }

  pinMode(_CS, OUTPUT);
  pinMode(_A0, OUTPUT);
  pinMode(_IC, OUTPUT);

  digitalWrite(_CS, HIGH); // latch
  digitalWrite(_A0, LOW);  // address
  digitalWrite(_IC, HIGH); // reset
}

byte getChipRegisterOffset(short reg)
{
  switch (reg & 0xFF)
  {
  case 0x08:
    return 1;
  case 0xBD:
    return 2;
  case 0x01:
  default:
    return 0;
  }
}

byte getChipRegister(short reg) {
  return chipRegisters[getChipRegisterOffset(reg)];
}

void setChipRegister(short reg, byte value)
{
  chipRegisters[getChipRegisterOffset(reg)] = value;
  senddata_ym3812(reg & 0xFF, value);
}

short getOperatorRegisterOffset(byte baseRegister, byte channel, byte operatorNum)
{
  channel = channel % OPL2_NUM_CHANNELS;
  operatorNum = operatorNum & 0x01;
  short offset = (channel * 10) + (operatorNum * 5);

  switch (baseRegister)
  {
  case 0x40:
    return offset + 1;
  case 0x60:
    return offset + 2;
  case 0x80:
    return offset + 3;
  case 0xE0:
    return offset + 4;
  case 0x20:
  default:
    return offset;
  }
}

byte getOperatorRegister(byte baseRegister, byte channel, byte operatorNum)
{
  return operatorRegisters[getOperatorRegisterOffset(baseRegister, channel, operatorNum)];
}

byte getRegisterOffset(byte channel, byte operatorNum)
{
  return registerOffsets[operatorNum % 2][channel % CHANNELS_PER_BANK];
}

void setOperatorRegister(byte baseRegister, byte channel, byte operatorNum, byte value)
{
  operatorRegisters[getOperatorRegisterOffset(baseRegister, channel, operatorNum)] = value;
  byte reg = baseRegister + getRegisterOffset(channel, operatorNum);
  senddata_ym3812(reg, value);
}

byte getChannelRegisterOffset(byte baseRegister, byte channel)
{
  channel = channel % OPL2_NUM_CHANNELS;
  byte offset = channel * 3;

  switch (baseRegister)
  {
  case 0xB0:
    return offset + 1;
  case 0xC0:
    return offset + 2;
  case 0xA0:
  default:
    return offset;
  }
}

void setChannelRegister(byte baseRegister, byte channel, byte value)
{
  channelRegisters[getChannelRegisterOffset(baseRegister, channel)] = value;
  byte reg = baseRegister + (channel % CHANNELS_PER_BANK);
  senddata_ym3812(reg, value);
}

byte getChannelRegister(byte baseRegister, byte channel)
{
  return channelRegisters[getChannelRegisterOffset(baseRegister, channel)];
}

void setBlock(byte channel, byte block)
{
  byte value = getChannelRegister(0xB0, channel) & 0xE3;
  setChannelRegister(0xB0, channel, value + ((block & 0x07) << 2));
}

void setKeyOn(byte channel, bool keyOn)
{
  byte value = getChannelRegister(0xB0, channel) & 0xDF;
  setChannelRegister(0xB0, channel, value + (keyOn ? 0x20 : 0x00));
}

void setFNumber(byte channel, short fNumber)
{
  byte value = getChannelRegister(0xB0, channel) & 0xFC;
  setChannelRegister(0xB0, channel, value + ((fNumber & 0x0300) >> 8));
  setChannelRegister(0xA0, channel, fNumber & 0xFF);
}

void playNote(byte channel, byte octave, byte note)
{
  setKeyOn(channel, false);
  setBlock(channel, min(octave, (byte)NUM_OCTAVES));
  setFNumber(channel, noteFNumbers[note % 12]);
  setKeyOn(channel, true);
}

void setTremolo(byte channel, byte operatorNum, bool enable)
{
  byte value = getOperatorRegister(0x20, channel, operatorNum) & 0x7F;
  setOperatorRegister(0x20, channel, operatorNum, value + (enable ? 0x80 : 0x00));
}

void setVibrato(byte channel, byte operatorNum, bool enable)
{
  byte value = getOperatorRegister(0x20, channel, operatorNum) & 0xBF;
  setOperatorRegister(0x20, channel, operatorNum, value + (enable ? 0x40 : 0x00));
}

void setMultiplier(byte channel, byte operatorNum, byte multiplier)
{
  byte value = getOperatorRegister(0x20, channel, operatorNum) & 0xF0;
  setOperatorRegister(0x20, channel, operatorNum, value + (multiplier & 0x0F));
}

void setAttack(byte channel, byte operatorNum, byte attack)
{
  byte value = getOperatorRegister(0x60, channel, operatorNum) & 0x0F;
  setOperatorRegister(0x60, channel, operatorNum, value + ((attack & 0x0F) << 4));
}

void setDecay(byte channel, byte operatorNum, byte decay)
{
  byte value = getOperatorRegister(0x60, channel, operatorNum) & 0xF0;
  setOperatorRegister(0x60, channel, operatorNum, value + (decay & 0x0F));
}

void setSustain(byte channel, byte operatorNum, byte sustain)
{
  byte value = getOperatorRegister(0x80, channel, operatorNum) & 0x0F;
  setOperatorRegister(0x80, channel, operatorNum, value + ((sustain & 0x0F) << 4));
}

void setRelease(byte channel, byte operatorNum, byte release)
{
  byte value = getOperatorRegister(0x80, channel, operatorNum) & 0xF0;
  setOperatorRegister(0x80, channel, operatorNum, value + (release & 0x0F));
}

void setVolume(byte channel, byte operatorNum, byte volume)
{
  byte value = getOperatorRegister(0x40, channel, operatorNum) & 0xC0;
  setOperatorRegister(0x40, channel, operatorNum, value + (volume & 0x3F));
}

void reset_ym3812()
{
  digitalWrite(_IC, LOW);
  delay(1);
  digitalWrite(_IC, HIGH);

  // Initialize chip registers.
  setChipRegister(0x00, 0x00);
  setChipRegister(0x08, 0x40);
  setChipRegister(0xBD, 0x00);

  // Initialize all channel and operator registers.
  for (byte i = 0; i < OPL2_NUM_CHANNELS; i++)
  {
    setChannelRegister(0xA0, i, 0x00);
    setChannelRegister(0xB0, i, 0x00);
    setChannelRegister(0xC0, i, 0x00);

    for (byte j = OPERATOR1; j <= OPERATOR2; j++)
    {
      setOperatorRegister(0x20, i, j, 0x00);
      setOperatorRegister(0x40, i, j, 0x3F);
      setOperatorRegister(0x60, i, j, 0x00);
      setOperatorRegister(0x80, i, j, 0x00);
      setOperatorRegister(0xE0, i, j, 0x00);
    }
  }
}

void setWaveFormSelect(bool enable) {
  if (enable) {
    setChipRegister(0x01, getChipRegister(0x01) | 0x20);
  } else {
    setChipRegister(0x01, getChipRegister(0x01) & 0xDF);
  }
}

void setInstrument(const byte data[12], byte channel, float volume) {
  volume = max((float)0.0, min(volume, (float)1.0));

  setWaveFormSelect(true);
  for (byte op = OPERATOR1; op <= OPERATOR2; op ++) {
    
    bool hasTremolo = data[op * 6 + 1] & 0x80 ? true : false;
    bool hasVibrato = data[op * 6 + 1] & 0x40 ? true : false;
    bool hasSustain = data[op * 6 + 1] & 0x20 ? true : false;
    bool hasEnvelopeScaling = data[op * 6 + 1] & 0x10 ? true : false;
    byte frequencyMultiplier = (data[op * 6 + 1] & 0x0F);
    byte keyScaleLevel = (data[op * 6 + 2] & 0xC0) >> 6;
    byte outputLevel = data[op * 6 + 2] & 0x3F;
    byte attack = (data[op * 6 + 3] & 0xF0) >> 4;
    byte decay = data[op * 6 + 3] & 0x0F;
    byte sustain = (data[op * 6 + 4] & 0xF0) >> 4;
    byte release = data[op * 6 + 4] & 0x0F;
    byte waveForm = data[op * 6 + 5] & 0x07;
    
    outputLevel = 63 - (byte)((63.0 - (float)outputLevel) * volume);

    setOperatorRegister(0x20, channel, op, (hasTremolo ? 0x80 : 0x00) + (hasVibrato ? 0x40 : 0x00) +
      (hasSustain ? 0x20 : 0x00) + (hasEnvelopeScaling ? 0x10 : 0x00) + (frequencyMultiplier & 0x0F));
    setOperatorRegister(0x40, channel, op, ((keyScaleLevel & 0x03) << 6) + (outputLevel & 0x3F));
    setOperatorRegister(0x60, channel, op, ((attack & 0x0F) << 4) + (decay & 0x0F));
    setOperatorRegister(0x80, channel, op, ((sustain & 0x0F) << 4) + (release & 0x0F));
    setOperatorRegister(0xE0, channel, op, (waveForm & 0x07));
  }
  
  byte feedback = (data[6] & 0x0E) >> 1;
  bool isAdditiveSynth = data[6] & 0x01 ? true : false;
  byte type = data[0];

  byte value = getChannelRegister(0xC0, channel) & 0xF0;
  setChannelRegister(0xC0, channel, value + ((feedback & 0x07) << 1) + (isAdditiveSynth ? 0x01 : 0x00));
}

void setPercussion(bool enable) {
  byte value = getChipRegister(0xBD) & 0xDF;
  setChipRegister(0xBD, value + (enable ? 0x20 : 0x00));
}

short getNoteFNumber(byte note) {
  return noteFNumbers[note % NUM_NOTES];
}

byte getDrums() {
  return getChipRegister(0xBD) & 0x1F;
}

void setDrums(byte drums) {
  byte value = getChipRegister(0xBD) & 0xE0;
  setChipRegister(0xBD, value);
  setChipRegister(0xBD, value + (drums & 0x1F));
}

void setDrums(bool bass, bool snare, bool tom, bool cymbal, bool hihat) {
  byte drums = 0;
  drums += bass   ? DRUM_BITS_BASS   : 0x00;
  drums += snare  ? DRUM_BITS_SNARE  : 0x00;
  drums += tom    ? DRUM_BITS_TOM    : 0x00;
  drums += cymbal ? DRUM_BITS_CYMBAL : 0x00;
  drums += hihat  ? DRUM_BITS_HI_HAT : 0x00;
  setDrums(drums);
}

void playDrum(byte drum, byte octave, byte note) {
  drum = drum % NUM_DRUM_SOUNDS;
  byte drumState = getDrums();

  setDrums(drumState & ~drumBits[drum]);
  byte drumChannel = drumChannels[drum];
  setBlock(drumChannel, min(octave, (byte)NUM_OCTAVES));
  setFNumber(drumChannel, noteFNumbers[note % NUM_NOTES]);
  setDrums(drumState | drumBits[drum]);
}

void setDrumInstrument(const byte data[12], float volume=1) {
  byte feedback = (data[6] & 0x0E) >> 1;
  bool isAdditiveSynth = data[6] & 0x01 ? true : false;
  byte type = data[0];
  
  volume = max((float)0.0, min(volume, (float)1.0));
  byte channel = drumChannels[type - INSTRUMENT_TYPE_BASS];

  setWaveFormSelect(true);
  for (byte op = OPERATOR1; op <= OPERATOR2; op ++) {    
    
    bool hasTremolo = data[op * 6 + 1] & 0x80 ? true : false;
    bool hasVibrato = data[op * 6 + 1] & 0x40 ? true : false;
    bool hasSustain = data[op * 6 + 1] & 0x20 ? true : false;
    bool hasEnvelopeScaling = data[op * 6 + 1] & 0x10 ? true : false;
    byte frequencyMultiplier = (data[op * 6 + 1] & 0x0F);
    byte keyScaleLevel = (data[op * 6 + 2] & 0xC0) >> 6;
    byte outputLevel = data[op * 6 + 2] & 0x3F;
    byte attack = (data[op * 6 + 3] & 0xF0) >> 4;
    byte decay = data[op * 6 + 3] & 0x0F;
    byte sustain = (data[op * 6 + 4] & 0xF0) >> 4;
    byte release = data[op * 6 + 4] & 0x0F;
    byte waveForm = data[op * 6 + 5] & 0x07;
    
    outputLevel = 63 - (byte)((63.0 - (float)outputLevel) * volume);
    byte registerOffset = drumRegisterOffsets[op][type - INSTRUMENT_TYPE_BASS];

    if (registerOffset != 0xFF) {
      setOperatorRegister(0x20, channel, op, (hasTremolo ? 0x80 : 0x00) +
        (hasVibrato ? 0x40 : 0x00) + (hasSustain ? 0x20 : 0x00) +
        (hasEnvelopeScaling ? 0x10 : 0x00) + (frequencyMultiplier & 0x0F));
      setOperatorRegister(0x40, channel, op, ((keyScaleLevel & 0x03) << 6) + (outputLevel & 0x3F));
      setOperatorRegister(0x60, channel, op, ((attack & 0x0F) << 4) + (decay & 0x0F));
      setOperatorRegister(0x80, channel, op, ((sustain & 0x0F) << 4) + (release & 0x0F));
      setOperatorRegister(0xE0, channel, op, (waveForm & 0x03));
    }
  }

  byte value = getChannelRegister(0xC0, channel) & 0xF0;
  setChannelRegister(0xC0, channel, value + ((feedback & 0x07) << 1) + (isAdditiveSynth ? 0x01 : 0x00));
}

#endif

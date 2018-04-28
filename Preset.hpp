#ifndef _PRESET_HPP_
#define _PRESET_HPP_

#include "Arduino.h"

class Preset
{
private:
  int8_t presetNumber;
  uint8_t presetMin;
  uint8_t presetMax;
  uint8_t currentBank;

  uint8_t command; // Program Change command
  uint8_t channel; // MIDI channel (counting from 0)
  
public:
  Preset();
  
  Preset(int8_t pNum, uint8_t pMin, uint8_t pMax, uint8_t bank);

  void presetUp();

  void presetDown();

  void setPreset(int8_t pNum);

  void setBank(uint8_t bank);

  void sendPresetMIDI(int8_t pNum);

};

#endif



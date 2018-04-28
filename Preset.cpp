#include "Preset.hpp"
#include "misc.hpp"

Preset::Preset()
  {
    presetNumber = 0;
    presetMin = 0;
    presetMax = 23;
    currentBank = 0;
    command = 0xC;
    channel = MIDI_CHANNEL -1;
  }
  
Preset::Preset(int8_t pNum, uint8_t pMin, uint8_t pMax, uint8_t bank) : presetNumber(pNum),
                                                                        presetMin(pMin),
                                                                        presetMax(pMax),
                                                                        currentBank(bank) {}

void Preset::presetUp()
{
  presetNumber++;
  if(presetNumber > presetMax) 
    presetNumber = presetMin;
  sendPresetMIDI(presetNumber);
}

void Preset::presetDown()
{
  presetNumber--;
  if(presetNumber < presetMin) 
    presetNumber = presetMax;
  sendPresetMIDI(presetNumber);
}

void Preset::setPreset(int8_t pNum)
{
  presetNumber = pNum;
  sendPresetMIDI(presetNumber);
}

void Preset::setBank(uint8_t bank)
{
  currentBank = bank;

  switch(bank)
  {
    case 0: // Presets bank 0: 1 - 24
        presetMin = 0;
        presetMax = 23;
        set_leds(1, 1, 1);
        break;
        
    case 1: // Presets bank: 1 - 5
        presetMin = 0;
        presetMax = 4;
        set_leds(1, 0, 0);

        // If current preset is  not in active bank, change it to the first preset in bank
        if(presetNumber < presetMin || presetNumber >presetMax)
        setPreset(presetMin);
        break;
        
    case 2: // Presets bank: 6 - 10
        presetMin = 5;
        presetMax = 9;
        set_leds(0, 1, 0);

        // If current preset is  not in active bank, change it to the first preset in bank
        if(presetNumber < presetMin || presetNumber >presetMax)
        setPreset(presetMin);
        break;
    
    case 3: // Presets bank: 11 - 15
        presetMin = 10;
        presetMax = 14;
        set_leds(0, 0, 1);

        // If current preset is  not in active bank, change it to the first preset in bank
        if(presetNumber < presetMin || presetNumber >presetMax)
        setPreset(presetMin);
        break;     
  }
}

void Preset::sendPresetMIDI(int8_t pNum)
{
  send_midi(command, channel, presetNumber);
}


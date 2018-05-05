#ifndef _MISC_HPP_
#define _MISC_HPP_

#include "Arduino.h"

//#define DEBUGGING_MODE

// Defined pin numbers
#define BUTTON_UP    2
#define BUTTON_DOWN  3
#define DEBOUNCE_DELAY_MS 250
#define LED1 9
#define LED2 7
#define LED3 8
// MIDI Channel - default is 1 in Line6 M5
#define MIDI_CHANNEL 1



void send_midi(uint8_t messageType, uint8_t channel, uint8_t data1);

void send_uart(uint8_t messageType, uint8_t channel, uint8_t data1);

void set_leds(bool led1, bool led2, bool led3);


#endif

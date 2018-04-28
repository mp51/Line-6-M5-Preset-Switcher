/*
   Line6 M5 MIDI preset switcher v0.3

   Preset switching:
   Next preset:     Button 1 (UP)
   Previous preset: Button 2 (DOWN)
   --------------------------------------------------------------------------
   Bank switching:
   Press both buttons:                Bank 0 (presets 1 - 24)
   (default on startup) - Indication:   LED1 (Green), LED2 (Red), LED3 (Blue)
                        -----------------------------------------------------
   Hold Button 1 (UP) for 1 second:   Bank 1 (presets 1 - 5)
                        - Indication:   LED1 (Green)
                        -----------------------------------------------------
   Hold Button 2 (DOWN) for 1 second: Bank 2 (presets 5 - 10)
                        - Indication:   LED2 (Red)
                        -----------------------------------------------------
   Hold both buttons for 1 second:    Bank 3 (presets 11 - 15)
                        - Indication:   LED3 (Blue)

   --------------------------------------------------------------------------
   Board: Arduino Pro Micro
   Wiring:
    MIDI Out    -> Tx0
    Button Up   -> Pin 2
    Button Down -> Pin 3
    LED1 (Green)-> Pin 9
    LED2 (Red)  -> Pin 7
    LED3 (Blue) -> Pin 8
   -----------------------

    Copyright (C) 2017 M.Pęczkowski
*/

#include "Preset.hpp"
#include "misc.hpp"

bool b1Flag = false;
bool b2Flag = false;
bool bothFlag = false;

unsigned long timePressed1;
unsigned long timePressed2;
unsigned long timePressedBoth;

Preset preset; // preset object

void setup() {

  // Start serial port with MIDI baud rate (31250)
  // Serial1: communication via Rx and Tx pins (Pro Micro)
  Serial1.begin(31250);

#ifdef DEBUGGING_MODE
  // Serial: UART communication via USB (Pro Micro) for debugging
  Serial.begin(9600);
#endif

  // Input buttons with pull-up resistors
  pinMode(BUTTON_UP, INPUT);
  digitalWrite(BUTTON_UP, HIGH);

  pinMode(BUTTON_DOWN, INPUT);
  digitalWrite(BUTTON_DOWN, HIGH);

  // LED outputs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  set_leds(1, 1, 1);
}

void loop() {

  // Only button 1 (UP) pressed
  if (!digitalRead(BUTTON_UP) && digitalRead(BUTTON_DOWN))
  {
    if (b1Flag == false)
    {
      b1Flag = true;
      timePressed1 = millis();
      preset.presetUp();
    } else
    {
      // Button 1 pressed for 1 second
      if ((millis() - timePressed1) > 1000)
      {
        // Presets bank 1: 0 - 4
        preset.setBank(1);
      }
    }
  } else
  {
    if ((millis() - timePressed1) > DEBOUNCE_DELAY_MS)
      b1Flag = false;
  }

  // Only button 2 (DOWN) pressed
  if (!digitalRead(BUTTON_DOWN) && digitalRead(BUTTON_UP))
  {
    if (b2Flag == false)
    {
      b2Flag = true;
      timePressed2 = millis();
      preset.presetDown();
    } else
    {
      // Button 2 pressed for 1 second
      if ((millis() - timePressed2) > 1000)
      {
        // Presets bank 2: 6 - 10
        preset.setBank(2);
      }
    }
  } else
  {
    if ((millis() - timePressed2) > DEBOUNCE_DELAY_MS)
      b2Flag = false;
  }

  // Both buttons pressed
  if (!digitalRead(BUTTON_UP) &&  !digitalRead(BUTTON_DOWN))
  {
    if (bothFlag == false)
    {
      bothFlag = true;
      timePressedBoth = millis();
      // Reset presets bank 0: 1 - 24
      preset.setBank(0);
    } else
    {
      // Both buttons pressed for 1 second
      if ((millis() - timePressedBoth) > 1000)
      {
        // Presets bank 3: 11 - 15
        preset.setBank(3);
      }
    }
  } else
  {
    bothFlag = false;
  }

}

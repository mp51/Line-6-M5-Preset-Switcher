/*
   Line6 M5 MIDI preset switcher

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
   Board: Arduino Pro Micro (Leonardo)
   Wiring:
    MIDI Out    -> Tx0
    Button Up   -> Pin 2
    Button Down -> Pin 3
    LED1 (Green)-> Pin 9
    LED2 (Red)  -> Pin 7
    LED3 (Blue) -> Pin 8
   -----------------------

    Written by Marcin Pęczkowski, 2018
*/

#include "Preset.hpp"
#include "misc.hpp"

volatile bool button1_pressed = false;
volatile bool button2_pressed = false;

volatile bool b1Flag = false;
volatile bool b2Flag = false;
volatile bool bothFlag = false;

volatile unsigned long timePressed1 = 0;
volatile unsigned long timePressed2 = 0;
volatile unsigned long timePressedBoth = 0;

Preset preset; // object for handling presets

void setup() {

  // Start serial port with MIDI baud rate (31250)
  // Serial1: communication via Rx and Tx pins (Pro Micro)
  Serial1.begin(31250);

#ifdef DEBUGGING_MODE
  // Serial: UART communication via USB (Pro Micro) for debugging
  Serial.begin(9600);
#endif

  // Input buttons with pull-up resistors
  pinMode(BUTTON_UP, INPUT_PULLUP);
  digitalWrite(BUTTON_UP, HIGH);

  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  digitalWrite(BUTTON_DOWN, HIGH);

  // LED outputs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // Light all LEDs
  set_leds(1, 1, 1);
}

void loop() {
  button1_pressed = !digitalRead(BUTTON_UP);
  button2_pressed = !digitalRead(BUTTON_DOWN);

  // Only button 1 (UP) pressed
  if (button1_pressed && !button2_pressed) {
    if ((b1Flag == false) && ((millis() - timePressed1) >= DEBOUNCE_DELAY_MS)) {
      b1Flag = true;
      timePressed1 = millis();
      preset.presetUp();
    } else {
      // Button 1 pressed for 1 second
      if ((millis() - timePressed1) > 1000) {
        // Presets bank 1: 0 - 4
        preset.setBank(1);
      }
    }
  } else if (b1Flag == true) { // Button released
    b1Flag = false;
    timePressed1 = millis();
  }

  // Only button 2 (DOWN) pressed
  if (button2_pressed && !button1_pressed) {
    if (b2Flag == false && ((millis() - timePressed2) >= DEBOUNCE_DELAY_MS)) {
      b2Flag = true;
      timePressed2 = millis();
      preset.presetDown();
    } else {
      // Button 2 pressed for 1 second
      if ((millis() - timePressed2) > 1000) {
        // Presets bank 2: 6 - 10
        preset.setBank(2);
      }
    }
  } else if (b2Flag == true) { // Button released
    b2Flag = false;
    timePressed2 = millis();
  }

  // Both buttons pressed
  if (button1_pressed &&  button2_pressed) {
    if (bothFlag == false  && ((millis() - timePressedBoth) >= DEBOUNCE_DELAY_MS)) {
      bothFlag = true;
      timePressedBoth = millis();
      // Reset presets bank 0: 1 - 24
      preset.setBank(0);
    } else {
      // Both buttons pressed for 1 second
      if ((millis() - timePressedBoth) > 1000) {
        // Presets bank 3: 11 - 15
        timePressedBoth = millis();
        preset.setBank(3);
      }
    }
  } else if (bothFlag == true) { // Buttons released
    timePressedBoth = millis();
    bothFlag = false;
  }
}
#include "misc.hpp"
#include "Arduino.h"

void send_midi(uint8_t messageType, uint8_t channel, uint8_t data1)
{
  Serial1.write(( messageType << 4 ) | channel); // send message type and channel byte
  Serial1.write(data1);                          // send data byte 1

#ifdef DEBUGGING_MODE
  // Debugging via USB UART
  send_uart(messageType, channel, data1);
#endif
}

void send_uart(uint8_t messageType, uint8_t channel, uint8_t data1)
{
  Serial.write(( messageType << 4 ) | channel); // send message type and channel byte
  Serial.write(data1);                          // send data byte 1
}

void set_leds(bool led1, bool led2, bool led3)
{
  digitalWrite(LED1, led1);
  digitalWrite(LED2, led2);
  digitalWrite(LED3, led3);
}

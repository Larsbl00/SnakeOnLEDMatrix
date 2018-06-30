#include "Pin.h"

////////////////
//Class funtions
////////////////
Pin::Pin(uint8_t pin, uint8_t mode)
{
  pinMode(pin, mode);
  this->pin = pin;
}

Pin::~Pin()
{
  
}

void Pin::Write(uint8_t value)
{
  digitalWrite(this->pin, value);
}

uint8_t Pin::Read()
{
  return (digitalRead(this->pin));
}

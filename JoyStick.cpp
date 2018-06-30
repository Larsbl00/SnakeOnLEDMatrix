#include "JoyStick.h"

#define map(CAST_TYPE, INPUT_VAL, MIN_VAL, MAX_VAL, MAP_MIN, MAP_MAX) ((CAST_TYPE)((double)INPUT_VAL/(MAX_VAL - MIN_VAL) * (MAP_MAX - MAP_MIN) + MAP_MIN)) 

////////////////
//Class funtions
////////////////

JoyStick::JoyStick(uint8_t analogPinX, uint8_t analogPinY) 
  : pinX(analogPinX), pinY(analogPinY)
{

}

JoyStick::~JoyStick()
{
  
}

float JoyStick::GetX()
{
  return map(float, analogRead(this->pinX), 0, 1023, -1, 1);
}

float JoyStick::GetY()
{
  return map(float, analogRead(this->pinY), 0, 1023, -1, 1);
}
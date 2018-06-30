#include "ShiftRegister.h"

#define LSB_BITMASK 0b1


////////////////
//Class funtions
////////////////

ShiftRegister::ShiftRegister(Pin dataPin, Pin clockPin, Pin latchPin)
  : dataPin(dataPin), clockPin(clockPin), latchPin(latchPin)
{
  latchPin.Write(1);
}

ShiftRegister::~ShiftRegister()
{
    
}

void ShiftRegister::SendByte(uint8_t byteToSend)
{
  this->latchPin.Write(0);
  this->sendByte(byteToSend);
  this->latchPin.Write(1);
}

void ShiftRegister::SendByteArray(uint8_t* byteArrayToSend, uint8_t arraySize)
{
  if (byteArrayToSend == NULL) return;
  this->latchPin.Write(0);
  for (uint8_t i = arraySize -1; i <= arraySize-1; i--)
  {
    this->sendByte(byteArrayToSend[i]);
  }
  this->latchPin.Write(1);
}

void ShiftRegister::Flush(uint8_t byteCount = 1)
{
  this->latchPin.Write(0);
  for (uint8_t i = 0; i < byteCount; i++) this->sendByte(0x00);
  this->latchPin.Write(1);
}

void ShiftRegister::sendByte(uint8_t byteToSend)
{
  for (uint8_t i = 7; i <= 7; i--)
  {
    this->clockPin.Write(0);
    this->dataPin.Write((byteToSend >> i) & LSB_BITMASK);
    this->clockPin.Write(1);
  }
}


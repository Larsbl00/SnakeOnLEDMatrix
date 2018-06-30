#include "LedMatrix.h"

#define MAX_LENGTH 8
#define MAX_WIDTH 8
#define LSB_BITMASK 1

#define disable_bit(BYTE_TO_CHANGE, INDEX) (BYTE_TO_CHANGE = BYTE_TO_CHANGE & ~(1 << INDEX))
#define write_bit(BYTE_TO_CHANGE, INDEX, VALUE) (BYTE_TO_CHANGE = BYTE_TO_CHANGE | ((VALUE & LSB_BITMASK) << INDEX))

void SetPoint(uint8_t field[8], Point point, uint8_t state)
{
  if (point.X >= MAX_WIDTH || point.Y >= MAX_LENGTH) 
  {
    Serial.println("Point is out of reach");
    return;
  } 

  disable_bit(field[point.Y], point.X);
  write_bit(field[point.Y], point.X, state);
}


////////////////
//Class funtions
///////////////

LedMatrix::LedMatrix(Pin dataPin, Pin clockPin, Pin latchPin) 
  : ledRegister(ShiftRegister(dataPin, clockPin, latchPin))
{
  
}

LedMatrix::~LedMatrix()
{
  
}


void LedMatrix::Send(uint8_t image[8])
{
  if (image == NULL) 
  {
    Serial.println("Image refers to NULL");
    return;
  }

  for (uint8_t i = 0; i < 8; i++)
  {
    uint8_t dataToSend[2];
    uint8_t currentRegisterIndex =  (1 << i);
    dataToSend[1] = ~image[i]; 
    dataToSend[0] = currentRegisterIndex;
    this->ledRegister.SendByteArray(dataToSend, 2);
  }
}

void LedMatrix::PlayAnimation(uint8_t animation[][8], uint8_t frameCount, uint32_t totalTimeToComplete)
{
  uint32_t timeNeededToCompleteFrame = millis() + (double)totalTimeToComplete/frameCount;
  if (millis() > this->animationLastTimePlayedFrame)
  {
    this->animationLastTimePlayedFrame = timeNeededToCompleteFrame;
    if (this->animationLastFramePlayed < (frameCount - 1))
    {
      this->animationLastFramePlayed++;
    } else 
    {
      this->animationLastFramePlayed = 0;
    }
  }

  this->Send(animation[this->animationLastFramePlayed]);
}

void LedMatrix::Flush()
{
  uint16_t byteCount = 2;
  this->ledRegister.Flush(byteCount);
}

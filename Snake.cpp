#include "Snake.h"

////////////////
//Class Funtions
////////////////
Snake::Snake(Point startPoint, const uint8_t maxLength, const uint32_t moveSpeedMillis)
  : body(new Point[maxLength]), maxLength(maxLength), moveSpeedMillis(moveSpeedMillis) 
{
  this->body[0] = startPoint;
  this->location = this->body[0];
  this->size = 1;
}

Snake::~Snake()
{

}

Point Snake::GetLocation()
{
  return this->location;
}

uint8_t Snake::GetLength()
{
  return this->size;
}

uint8_t Snake::GetMaxLength()
{
  return this->maxLength;
}

void Snake::Move(int8_t x, int8_t y, uint8_t width, uint8_t height)
{
  if (millis() - this->lastTimeMoved >= this->moveSpeedMillis)
  {
    this->updateBody();

    this->location.X += x;
    if (this->location.X >= width) this->location.X -= width;
    else if (this->location.X < 0) this->location.X += width;

    this->location.Y += y;
    if (this->location.Y >= height) this->location.Y -= height;
    else if (this->location.Y < 0) this->location.Y += height; 

    this->body[0] = this->location;
    this->lastTimeMoved = millis();
  }
}

uint8_t Snake::CheckIfHeadHitsBody()
{
  for (uint8_t i = 1; i < this->size-1; i++)
  {
    if (PointCompare(this->body[i], this->location, MeasureModePoints::CHECK_IF_EQUAL)) return 1;
  }
  return 0;
}

void Snake::AddBody()
{
  if (this->size + 1 >= this->maxLength) return;
  this->size++;
  this->body[this->size-1] = this->body[this->size - 2];
}

uint8_t Snake::Eat(Point point)
{
  return PointCompare(this->location, point, MeasureModePoints::CHECK_IF_EQUAL);
}

void Snake::DrawOnField(uint8_t field[8])
{
  for(uint8_t i = 0; i < this->size; i++)
  {
    SetPoint(field, this->body[i], 1);
  }
}

void Snake::updateBody()
{
    for (uint8_t i = this->size-1; i > 0; i--)
    {
      this->body[i] = this->body[i-1];
    } 
}
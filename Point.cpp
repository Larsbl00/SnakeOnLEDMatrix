#include "Point.h"

int8_t PointCompare(Point p1, Point p2, MeasureModePoints mode)
{
  switch (mode) 
  {
    case MeasureModePoints::CHECK_HIGHER_X:
      return (p1.X - p2.X);

    case MeasureModePoints::CHECK_HIGHER_Y:
      return (p1.Y - p2.Y);

    case MeasureModePoints::CHECK_IF_EQUAL:
      if ((p1.X == p2.X) && (p1.Y == p2.Y)) 
      {
        return 1;
      } 
      else
      {
        return 0;
      }

    default: return 0;
  }
  return((p1.X + p1.X) - (p2.X + p2.Y));
}
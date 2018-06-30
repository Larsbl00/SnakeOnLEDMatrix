/**
 * @brief Point.h Makes it easy to give a location as a parameter. And gives you a function to easily compare points
 * 
 * @file Point.h
 * @author Lars Bloemers
 * @date 2018-06-30
 */

#include <stdint.h>
#include <stdio.h>

#ifndef POINT_H
#define POINT_H

typedef struct Point 
{
  int8_t X;
  int8_t Y;
} Point; 

typedef enum
{
  CHECK_HIGHER_X,
  CHECK_HIGHER_Y,
  CHECK_IF_EQUAL
} MeasureModePoints;


/**
 * @brief Compares two points
 * 
 * @param p1 First point
 * @param p2 Second point
 * @param mode Indicates how it's measured
 * @return int8_t Return depends on the MeasureModePoints
 * if mode = CHECK_HIGHER_X -> returns difference between the x-values
 * if mode = CHECK_HIGHER_Y -> returns difference between the y-values
 * if mode = CHECK_IF_EQUAL -> returns 1 if points are equal, 0 if not
 */
int8_t PointCompare(Point p1, Point p2, MeasureModePoints mode);

#endif
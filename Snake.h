/**
 * @brief This contains a snake class. So I can play snake on my led matrix
 * 
 * @file Snake.h
 * @author Lars Bloemers
 * @date 2018-06-30
 */

#include <stdio.h>
#include <stdint.h>
#include "Point.h"
#include "LedMatrix.h"

#ifndef SNAKE_H
#define SNAKE_H

class Snake 
{
  public:

    /**
     * @brief Construct a new Snake object
     * 
     * @param startPoint Point to start the snake
     * @param maxLength The maximum length that the snake can be
     * @param moveSpeedMillis Milliseconds need to complete 1 move
     */
    Snake(Point startPoint, const uint8_t maxLength, const uint32_t moveSpeedMillis);

    /**
     * @brief Destroy the Snake object
     * 
     */
    ~Snake();

    /**
     * @brief Get the Location object
     * 
     * @return Point Returns the location of the head
     */
    Point GetLocation();

    /**
     * @brief Get the Length object
     * 
     * @return uint8_t Current length of the snake
     */
    uint8_t GetLength();

    /**
     * @brief Get the Max Length object
     * 
     * @return uint8_t Returns the max length of the snake
     */
    uint8_t GetMaxLength();

    /**
     * @brief Get the Move Speed Millis object
     * 
     * @return uint32_t Returns how long it takes to make 1 move
     */
    uint32_t GetMoveSpeedMillis();

    /**
     * @brief Moves the snake with a given x and y value
     * 
     * @param x Moves by a given amount on the x-axis
     * @param y Moves by a given amount on the y-axis
     * @param width Width of the field
     * @param height Height of the field
     */
    void Move(int8_t x, int8_t y, uint8_t width, uint8_t height);

    /**
     * @brief Checks if the head hits it's body
     * 
     * @return uint8_t Returns 1 if it hit itself, 0 if not
     */
    uint8_t CheckIfHeadHitsBody();

    /**
     * @brief Adds an item to the body
     * 
     */
    void AddBody();

    /**
     * @brief Checks of the given point is edible 
     * 
     * @param point 
     * 
     * @return uint8_t Returns 1 if it is within reach, 0 if not
     */
    uint8_t Eat(Point point);

    /**
     * @brief Draws the snake on a matrix
     * 
     * @param field The uint8_t array to draw on
     * @param height The height
     */
    void DrawOnField(uint8_t field[8]);

  private:
    Point* body = NULL;
    Point location;
    uint8_t size; 
    uint8_t maxLength;
    uint32_t moveSpeedMillis;
    uint32_t lastTimeMoved;

    void updateBody();
};

#endif
/**
 * @brief Contains a class to easily control an LED matrix with only 3 pins
 * 
 * @file LedMatrix.h
 * @author Lars Bloemers
 * @date 2018-06-29
 */

#include <Arduino.h>
#include <stdint.h>
#include <math.h>
#include "ShiftRegister.h"
#include "Point.h"

#ifndef LEDMATRIX_H
#define LEDMATRIX_H

/**
 * @brief Sets a Coordinate to a given state in a byte Array
 * 
 * @param field A pointer to the field to turn the point on or off in
 * @param point Point to turn on or off
 * @param state Turns the light on or off
 * note: it'll only pay attention to the LSB
 */
void SetPoint(uint8_t field[8], Point point, uint8_t state);

class LedMatrix
{
  public:

    /**
     * @brief Construct a new Led Matrix object that's 8 by 8 pixels long, controlled byte a 16-bit register
     * or two 8-bit registers
     * 
     * @param dataPin Pin to send the data through
     * @param clockPin The pin that funtions as the clock
     * @param latchPin The pin to enable data flowing in
     */
    LedMatrix(Pin dataPin, Pin clockPin, Pin latchPin);

    /**
     * @brief Destroy the Led Matrix object
     * 
     */
    ~LedMatrix();

    /**
     * @brief Sends an 8x8 image to the Matrix
     * 
     * @param image Image to send
     */
    void Send(uint8_t image[8]);

    /**
     * @brief Plays an animation, with a dimension of 8x8
     * 
     * @param animation Array of frames
     * @param frameCount Count of all frames
     * @param totalTimeToComplete Time needed to complete the entire animation
     */
    void PlayAnimation(uint8_t animation[][8], uint8_t frameCount, uint32_t totalTimeToComplete);

    /**
     * @brief Flushes the register
     * 
     */
    void Flush();

    ShiftRegister LedRegister(){ return this->ledRegister; }

  private:
    ShiftRegister ledRegister;
    uint32_t animationLastTimePlayedFrame = 0;
    uint8_t animationLastFramePlayed = 0;
};

#endif

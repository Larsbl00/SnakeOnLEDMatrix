/**
 * @brief Creates an easy-to-use class for a JoyStick.
 * 
 * @file JoyStick.h
 * @author Lars Bloemers
 * @date 2018-06-30
 */

#include <stdint.h>
#include <Arduino.h>


#ifndef JOYSTICK_H
#define JOYSTICK_H

class JoyStick 
{
  public:

    /**
     * @brief Construct a new Joy Stick object
     * 
     * @param analogPinX Pin bound to reading X-values
     * @param analogPinY Pin bound to reading Y-values
     */
    JoyStick(uint8_t analogPinX, uint8_t analogPinY);

    /**
     * @brief Destroy the Joy Stick object
     * 
     */
    ~JoyStick();

    /**
     * @brief Gets the X-value
     * 
     * @return float Returns a value between -1(left) and 1(Right)
     */
    float GetX();

    /**
     * @brief Gets the Y-value
     * 
     * @return float Returns a value between -1(Bottom) and 1(Top)
     */
    float GetY();

  private:

    uint8_t pinX;
    uint8_t pinY;
};

#endif
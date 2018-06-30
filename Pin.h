/**
 * @brief The pin class is used for the shiftRegister class. If you can't use the pinMode and digitalRead functions,
 *  you only need to rewrite this class and the register will still work
 * 
 * @file Pin.h
 * @author Lars Bloemers
 * @date 2018-06-30
 */

#include <stdint.h>
#include <Arduino.h>

#ifndef PIN_H
#define PIN_H

class Pin
{
  public:

    uint8_t PinNumber() { return this->pin; }

    /**
     * @brief Construct a new Pin object
     * 
     * @param pin The pin to which the register is bound, will not work on all platforms
     *  unless they support, digitalWrite
     * 
     * @param pinMode The mode to which the pin needs to be written
     */
    Pin(uint8_t pin, uint8_t mode);

    /**
     * @brief Destroy the Pin object
     * 
     */
    ~Pin();

    /**
     * @brief Writes the pin to a certain value
     * 
     * @param value 
     */
    void Write(uint8_t value);

    /**
     * @brief Read the value of the pin
     * 
     * @return uint8_t 
     */
    uint8_t Read();

  private:
    uint8_t pin;

};

#endif

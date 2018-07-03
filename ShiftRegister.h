/**
 * @brief The shift register class makes it easy to send data to a shift register, if you can't send data to your register
 *  please make sure it's correctly wired and that the pin class is compatable with your device
 * 
 * @file ShiftRegister.h
 * @author Lars Bloemers
 * @date 2018-06-30
 */

#include <stdint.h>
#include <Arduino.h>
#include <stdio.h>
#include "Pin.h"

#ifndef SHIFTREGISTER_H
#define SHIFTREGISTER_H

class ShiftRegister
{
  public:

    /**
     * @brief Construct a new Shift Register object
     * 
     * @param dataPin Pin to send the data through
     * @param clockPin The pin that funtions as the clock
     * @param latchPin The pin to enable data flowing in
     */
    ShiftRegister(Pin dataPin, Pin clockPin, Pin latchPin);

    /**
     * @brief Destroy the Shift Register object
     * 
     */
    ~ShiftRegister();

    /**
     * @brief Sends a byte to the register
     * 
     * @param byteToSend This is the byte to send
     */
    void SendByte(uint8_t byteToSend);

    /**
     * @brief Sends an array of bytes(if you want to send a uint32_t, just send a 4 dimensional uint8_t array)
     * note: This funtions is baised on a chain from left to right
     * 
     * @param byteArrayToSend The array to send to the register
     */
    void SendByteArray(uint8_t* byteArrayToSend, uint8_t arraySize);

    /**
     * @brief Flushes the registers
     * 
     * @param byteCount Amount of bytes that need to be flushed
     */
    void Flush(uint8_t byteCount = 1);

  private:
    Pin dataPin;
    Pin clockPin; 
    Pin latchPin;

    /**
     * @brief Actions need to send, does not lower latchPin. Data will be send with th LSB going first
     * 
     * @param byteToSend Byte to send through
     */
    void sendByte(uint8_t byteToSend);
};

#endif

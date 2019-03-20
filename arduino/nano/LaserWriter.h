#ifndef _LASERWRITER_H_
#define _LASERWRITER_H_


#include <Arduino.h>

/******************************************************************************
 *  @brief: readInBuffer
 *  reads input from the laser into a buffer
 *****************************************************************************/
class LaserWriter {
public:
    int pulsePeriod;
    int laserPin;


    LaserWriter(int recvPulsePeriod, int recvLaserPin); // constructor
    ~LaserWriter(); // destructor

    // reads from Serial.read() until newline and returns string
    void readFromUser();

    // outputs message to laser
    void outputMessage(String message);
};

#endif

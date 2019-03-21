/*# ---------------------------------------------------
#    Name: Konrad Staniszewski, Andrew Rooney
#    ID: 1531593, 1496508
#    CMPUT 275, W 2018
#    Final Project: Laser Communications
# ---------------------------------------------------*/

#ifndef _SENSORREADER_H_
#define _SENSORREADER_H_

#include <Arduino.h>


/******************************************************************************
 *  @brief: SensorReader
 *  Class used to interact with the sensor
 *****************************************************************************/
class SensorReader {
public:
    SensorReader(char recvSensorPin, int recvPulsePeriod, int recvSensorThreshold); // constructor
    ~SensorReader(); // destructor

    // read in a buffer of sensor size
    void readInBufferOld(int bufferSize);

    // read in a boolean binary array of size bufferSize and return a point to array
    bool * readInBuffer(int bufferSize);

private:
	char sensorPin;
    int pulsePeriod;
    int threshold;
};

#endif
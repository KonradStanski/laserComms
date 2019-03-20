/*# ---------------------------------------------------
#    Name: Konrad Staniszewski, Andrew Rooney
#    ID: 1531593, 1496508
#    CMPUT 275, W 2018
#    Final Project: Laser Communications
# ---------------------------------------------------*/

#ifndef _SENSORREADER_H_
#define _SENSORREADER_H_

#include <Arduino.h>


// define laserReader class
class SensorReader {
public:
    SensorReader(char recvSensorPin, int recvPulsePeriod); // constructor
    ~SensorReader(); // destructor

    void readInBuffer(int bufferSize); // read in a buffer of sensor size


private:
	char sensorPin;
    int pulsePeriod;
};

#endif

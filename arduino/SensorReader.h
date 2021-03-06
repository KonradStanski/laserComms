/*# ---------------------------------------------------
#    Name: Konrad Staniszewski, Andrew Rooney
#    ID: 1531593, 1496508
#    CMPUT 275, W 2018
#    Final Project: Laser Communications
# ---------------------------------------------------*/

#ifndef _SENSORREADER_H_
#define _SENSORREADER_H_

#include <Arduino.h>
#define stSuccess 1
#define stFail 0

/******************************************************************************
 *  @brief: SensorReader
 *  Class used to interact with the sensor
 *****************************************************************************/
class SensorReader {
public:
    SensorReader(char recvSensorPin, uint32_t recvPulsePeriod, int recvSensorThreshold); // constructor
    ~SensorReader(); // destructor
    byte* unHamByte(byte* buffer);
    byte* readInBuffer(int bufferSize); // read in buffer from sensor
    bool recvHeader(); // returns true if message commence is recieved
    int recvHeadSize();
    int recvPair();
    bool waitForAck();
private:
	char sensorPin; // pin to which sensor is atached to
    uint32_t pulsePeriod; // period to wait inbetween receiving signals
    int threshold; // 10 bit threshold value 0-1024. 600 works well
};

#endif

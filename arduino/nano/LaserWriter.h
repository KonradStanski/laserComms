/*# ---------------------------------------------------
#    Name: Konrad Staniszewski, Andrew Rooney
#    ID: 1531593, 1496508
#    CMPUT 275, W 2018
#    Final Project: Laser Communications
# ---------------------------------------------------*/

#ifndef _LASERWRITER_H_
#define _LASERWRITER_H_

#include <Arduino.h>

/******************************************************************************
 *  @brief: readInBuffer
 *  reads input from the laser into a buffer
 *****************************************************************************/
class LaserWriter {
public:
    LaserWriter(int recvLaserPin, int recvPulsePeriod); // constructor
    ~LaserWriter(); // destructor

    // reads from Serial.read() until newline and returns string
    void readFromUser();

	// outputs message to laser
	void outputMessage(String message);

private:
	int pulsePeriod;
	int laserPin;
};

#endif

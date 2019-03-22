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
 *  @brief: LaserWriter
 *  Class used to interact with the laser
 *****************************************************************************/
class LaserWriter {
public:
    LaserWriter(int recvLaserPin, int recvPulsePeriod); // constructor
    ~LaserWriter(); // destructor

    // reads from Serial.read() until newline and returns string
    void readFromUser();

	// outputs message to laser
	void outputMessage(char buffer[], int bufferSize);

private:
	int pulsePeriod;
	int laserPin;
};

#endif

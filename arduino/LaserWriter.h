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
    LaserWriter(int recvLaserPin, uint32_t recvPulsePeriod); // constructor
    ~LaserWriter(); // destructor

    // reads from Serial.read() until newline and returns string
    void readFromUser();

	void sendBuffer(char buffer[], int bufferSize);
	void sendHeader();

	void pulseHigh();
	void pulseLow();


	char * charToHamming(char inChar);


private:
	uint32_t pulsePeriod;
	int laserPin;
};

#endif

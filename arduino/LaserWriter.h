/*# ---------------------------------------------------
#    Name: Konrad Staniszewski, Andrew Rooney
#    ID: 1531593, 1496508
#    CMPUT 275, W 2018
#    Final Project: Laser Communications
# ---------------------------------------------------*/

#ifndef _LASERWRITER_H_
#define _LASERWRITER_H_
#define stSuccess 1
#define stFail 0
#include <Arduino.h>


/******************************************************************************
 *  @brief: LaserWriter
 *  Class used to interact with the laser
 *****************************************************************************/
class LaserWriter {
public:
    LaserWriter(int recvLaserPin, uint32_t recvPulsePeriod); // constructor
    ~LaserWriter(); // destructor
  void sendACK( void );
	void sendBuffer(byte buffer[], int bufferSize);
	void sendHeader();
    void sendHeadSize(int bufferSize);
	byte * charToHam(char inChar);

	void pulseHigh();
	void pulseLow();

    void readFromUser();



private:
	uint32_t pulsePeriod;
	int laserPin;
};

#endif

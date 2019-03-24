/*# ---------------------------------------------------
#    Name: Konrad Staniszewski, Andrew Rooney
#    ID: 1531593, 1496508
#    CMPUT 275, W 2018
#    Final Project: Laser Communications
# ---------------------------------------------------*/

#include "SensorReader.h"
#include <Arduino.h>


/******************************************************************************
 *  @brief: SensorReader // constructor //
 *  Instanciate SensorReader instance
 *****************************************************************************/
SensorReader::SensorReader(char recvSensorPin, uint32_t recvPulsePeriod, int recvSensorThreshold) {
    sensorPin = recvSensorPin;
    pulsePeriod = recvPulsePeriod;
    threshold = recvSensorThreshold;
}


/******************************************************************************
 *  @brief: SensorReader // destructor //
 *  Destruc insance of SensorReader
 *****************************************************************************/
SensorReader::~SensorReader() {
}


void SensorReader::unHam(char buffer[], int bufferSize){
	// getting [p1 p2 x3 p3 x2 x1 x0]
	bool s1, s2, s3;
	s1 = atoi(buffer[n+0])^atoi(buffer[n+2])^atoi(buffer[n+4])^atoi(buffer[n+6]);
	s2 = atoi(buffer[n+2])^atoi(buffer[n+2])^atoi(buffer[n+5])^atoi(buffer[n+6]);
	s3 = atoi(buffer[n+3])^atoi(buffer[n+4])^atoi(buffer[n+5])^atoi(buffer[n+6]);


}


/******************************************************************************
 *  @brief: readInBuffer
 *  reads in a char array of '1' or '0' of size bufferSize and
    returns a pointer to a char array.
    READS ARRAY IN MSB FIRST
 *****************************************************************************/
char * SensorReader::readInBuffer(int bufferSize) {
    delay(pulsePeriod/2); // delay to offset communications
    // Serial.print("create buffer : ");
    // init binary array
    char *buffer = (char*)malloc(sizeof(char[bufferSize]));
    // fill array with binary values
    for (int i = 0; i < bufferSize; i++) {
        int lightRead = analogRead(sensorPin);
        if (lightRead > threshold) {
            buffer[i] = '1';
            // Serial.print("1");
            delay(pulsePeriod);
        }
        else {
            buffer[i] = '0';
            // Serial.print("0");
            delay(pulsePeriod);
        }
    }
    // Serial.println(" : return");
    unHam(buffer, bufferSize);
    return buffer;
}


/******************************************************************************
 *  @brief: recvHeader
 *  State Machine for checking if a specified header is read in. Currently is
    set to read in **0xFF**
 *****************************************************************************/
bool SensorReader::recvHeader() {
    //read in 0xFF
    // begin reading in code
    if(analogRead(sensorPin) > threshold) {
        Serial.println("might recieve code!");
        for (int i = 0; i < 2; i++) {
            if (!(analogRead(sensorPin) > threshold)) {
                // recieved 0
                Serial.println("received 0 exit cond");
                return false;
            }
            else{
                // recieved 1
                delay(pulsePeriod);
            }
        }
        Serial.println("recieved code!");
        return true;
    }
    return false;
}

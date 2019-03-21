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
SensorReader::SensorReader(char recvSensorPin, int recvPulsePeriod, int recvSensorThreshold) {
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


/******************************************************************************
 *  @brief: readInBuffer
 *  reads in a binary array of size bufferSize and returns a pointer to a
    boolean array.
 *****************************************************************************/
bool * SensorReader::readInBuffer(int bufferSize) {
    // init binary array
    bool binArray[bufferSize] = {false};
    // fill array with binary values
    for (int i = 0; i < bufferSize; i++) {
        int lightRead = analogRead(sensorPin);
        if (lightRead > threshold) {
            binArray[i] = true;
        }
        delay(pulsePeriod);
    }
    return binArray;
}


/******************************************************************************
 *  @brief: readInBufferOld
 *  reads input from the laser into a buffer
 *****************************************************************************/
void SensorReader::readInBufferOld(int bufferSize) {
    // Initialize the int ascii val to 0
    int lightRead;
    int readVal = 0;

    // read in 7 binary values and calculate the equivalent decimal representation
    for (int i = bufferSize; i >= 0; i--){
        lightRead = analogRead(sensorPin); // read the pin value
        if (lightRead > 600) { // trigger if light is hitting the pin
            readVal += (int) (pow(2, i) + 0.1); // the 0.1 is added because pow returns a double that is rounded down?
        }
        delay(pulsePeriod);
    }
    Serial.print("Integer val: ");
    Serial.print(readVal);
    Serial.print(" Ascii Char: ");
    Serial.println(char(readVal));
}




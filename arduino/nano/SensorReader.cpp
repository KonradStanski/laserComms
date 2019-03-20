/*# ---------------------------------------------------
#    Name: Konrad Staniszewski, Andrew Rooney
#    ID: 1531593, 1496508
#    CMPUT 275, W 2018
#    Final Project: Laser Communications
# ---------------------------------------------------*/

#include "SensorReader.h"
#include <Arduino.h>

// constructor
SensorReader::SensorReader(char recvSensorPin, int recvPulsePeriod) {
	sensorPin = recvSensorPin;
	pulsePeriod = recvPulsePeriod;
}

// destructor
SensorReader::~SensorReader() {
}

/******************************************************************************
 *  @brief: readInBuffer
 *  reads input from the laser into a buffer
 *****************************************************************************/
void SensorReader::readInBuffer(int bufferSize) {
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

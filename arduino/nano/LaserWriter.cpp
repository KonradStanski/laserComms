#include "LaserWriter.h"
#include <Arduino.h>

// constructor
LaserWriter::LaserWriter(int recvPulsePeriod, int recvLaserPin){
    pulsePeriod = recvPulsePeriod;
    laserPin = recvLaserPin;
}

// destructor
LaserWriter::~LaserWriter(){
}

// read message from terminal
void LaserWriter::readFromUser() {
    //Variable Definitions
    // wait untl
    if (Serial.available()) {
        char inChar = Serial.read(); // read in character
        Serial.print("typed: ");
        Serial.print(inChar);
        Serial.print(", ascii value: ");
        Serial.print((int)inChar);
        Serial.print(", ascii binary value: ");
        for (int i = 7; i >= 0; i--) { // unsure if this is the right order
            int bitVal = bitRead((int)inChar, i);
            Serial.print(bitVal);
            if (bitVal) {
                // pulse a "1"
                digitalWrite(laserPin, HIGH);
                delay(pulsePeriod);
                digitalWrite(laserPin, LOW);
            }
            else {
                // pulse a "0"
                delay(pulsePeriod);
            }

        }
        Serial.println(" ");
    }
}

void LaserWriter::outputMessage(String message) {

}

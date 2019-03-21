/*# ---------------------------------------------------
#    Name: Konrad Staniszewski, Andrew Rooney
#    ID: 1531593, 1496508
#    CMPUT 275, W 2018
#    Final Project: Laser Communications
# ---------------------------------------------------*/

#include "LaserWriter.h"
#include <Arduino.h>


/******************************************************************************
 *  @brief: LaserWriter // constructor //
 *  instantiate LaserWriter instance
 *****************************************************************************/
LaserWriter::LaserWriter(int recvLaserPin, int recvPulsePeriod){
    pulsePeriod = recvPulsePeriod;
    laserPin = recvLaserPin;
}


/******************************************************************************
 *  @brief: LaserWriter // destructor //
 *  destruct LaserWriter instance
 *****************************************************************************/
LaserWriter::~LaserWriter(){
}


/******************************************************************************
 *  @brief: readFromUser()
 *  read a character from screen and output it to the laser
 *****************************************************************************/
void LaserWriter::readFromUser() {
    // wait until available
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


/******************************************************************************
 *  @brief: outPutMessage
 *  Given a message, write it to the laser.
 *****************************************************************************/
void LaserWriter::outputMessage(String message) {

}
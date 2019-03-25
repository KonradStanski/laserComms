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
LaserWriter::LaserWriter(int recvLaserPin, uint32_t recvPulsePeriod){
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
 *  @brief: outPutMessage
 *  Given a message, write it to the laser.
 *****************************************************************************/
void LaserWriter::sendBuffer(byte buffer[], int bufferSize) {
    for (int i = 0; i < bufferSize; i++) {
        if (buffer[i] == 1) {
            pulseHigh();
        }
        else {
            pulseLow();
        }
    }
}


/******************************************************************************
 *  @brief: outPutMessage
 *  Given a message, write it to the laser.
 *****************************************************************************/
void LaserWriter::sendHeader() {
    for (int i = 0; i < 2; i++) {
        digitalWrite(laserPin, HIGH);
        delay(pulsePeriod);
    }
}



byte * LaserWriter::charToHam(char inChar) {
    int xn[8];
    int intVal = (int)inChar;
    int p1, p2, p3, p4, p5, p6;
    // assign buffer
    byte *buffer = (byte*)malloc(sizeof(byte[14]));
    for (int i = 0; i < 8; i++) {
        if (bitRead(intVal, i)) {
            xn[i] = 1;
        }
        else {
            xn[i] = 0;
        }
    }
    // set parity bits for first half
    p1 = xn[3]^xn[2]^xn[0];
    p2 = xn[3]^xn[1]^xn[0];
    p3 = xn[2]^xn[1]^xn[0];
    // set parity bit for second half
    p4 = xn[7]^xn[6]^xn[4];
    p5 = xn[7]^xn[5]^xn[4];
    p6 = xn[6]^xn[5]^xn[4];

    // construct char array
    buffer[0] = p1;
    buffer[1] = p2;
    buffer[2] = xn[3];
    buffer[3] = p3;
    buffer[4] = xn[2];
    buffer[5] = xn[1];
    buffer[6] = xn[0];
    buffer[7] = p4;
    buffer[8] = p5;
    buffer[9] = xn[7];
    buffer[10] = p6;
    buffer[11] = xn[6];
    buffer[12] = xn[5];
    buffer[13] = xn[4];
    buffer[9] = 1;
    return buffer;
}


void LaserWriter::pulseHigh() {
    // pulse a "1"
    digitalWrite(laserPin, HIGH);
    delay(pulsePeriod);
    digitalWrite(laserPin, LOW);
}


void LaserWriter::pulseLow() {
    // pulse a "0"
    digitalWrite(laserPin, LOW);
    delay(pulsePeriod);
}


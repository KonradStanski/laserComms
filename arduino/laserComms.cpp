/*# ---------------------------------------------------
#    Name: Konrad Staniszewski, Andrew Rooney
#    ID: 1531593, 1496508
#    CMPUT 275, W 2018
#    Final Project: Laser Communications
# ---------------------------------------------------*/

#include <Arduino.h>
#include "LaserWriter.h"
#include "SensorReader.h"

// pin definitions
int laserPin = 4;
char sensorPin = A7;
uint32_t pulsePeriod = 10; //milliseconds
int threshold = 930;


/******************************************************************************
 *  @brief: serialPrintBuffer
 *  prints the values from a binary char buffer in dec, bin, ascii,
 *****************************************************************************/
void serialPrintBuffer(byte * buffer, int bufferSize) {
    Serial.print("Print buffer : ");
    int intVal = 0;
    for (int i = 0; i < bufferSize; i++) {
        if(buffer[i]) {
            // Serial.println("1");
            Serial.print(buffer[i]);
            intVal += bit(i);
        }
        else {
            // Serial.println("0");
            Serial.print(buffer[i]);
        }
    }
    // convert to decimal
    Serial.print(" : DEC: ");
    Serial.print(intVal);
    // convert to ascii
    Serial.print(" : ASCII: ");
    Serial.print(char(intVal));
    //done
    Serial.println(" : done");
    Serial.println();
}


/******************************************************************************
 *  @brief: sendHamFromUser
 *  funciton for laser control to send hamming codes to a reciever
 *****************************************************************************/
void sendHamFromUser(LaserWriter laser) {
    byte * buffer;
    int hamBufferSize = 14;
    char inChar = Serial.read();
    buffer = laser.charToHam(inChar);
    // flip a bit
    buffer[6] = !buffer[6];
    buffer[9] = !buffer[9];
    // send message
    laser.sendHeader();
    laser.sendBuffer(buffer, hamBufferSize);
    serialPrintBuffer(buffer, hamBufferSize);
    delay(60); // needed to avoid overlap of signal
    free(buffer);
}


/******************************************************************************
 *  @brief: recvHamFromUser
 *  This funciton controls the useage of the sensor class to receive hamming
    codes.
 *****************************************************************************/
void recvHamFromUser(SensorReader sensor) {
    // instanciate buffer for the hamming code and resulting char
    byte * buffer;
    byte * charBuffer;
    int hamBufferSize = 14;
    int charBufferSize = 8;
    // read in hamming buffer
    buffer = sensor.readInBuffer(hamBufferSize);
    serialPrintBuffer(buffer, hamBufferSize);
    // convert buffer to char
    charBuffer = sensor.unHamByte(buffer);
    serialPrintBuffer(charBuffer, charBufferSize);
    free(buffer);
    free(charBuffer);
}


// Arduino Setup Configuration
void setup() {
    init();
    Serial.begin(9600);
    pinMode(sensorPin, INPUT);
    pinMode(laserPin, OUTPUT);
    digitalWrite(laserPin, LOW);
}


// main running function
int main() {
    setup();
    //Instanciate a laser writer and a sensor reader
    LaserWriter laser(laserPin, pulsePeriod);
    SensorReader sensor(sensorPin, pulsePeriod, threshold);

    while(true) {
        if (Serial.available()) {
            sendHamFromUser(laser);
        }
        if (sensor.recvHeader()) {
            recvHamFromUser(sensor);
        }
    }
    return 0;
}

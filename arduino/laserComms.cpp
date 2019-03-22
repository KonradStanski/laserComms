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
int pulsePeriod = 20;
int threshold = 600;


/******************************************************************************
 *  @brief: serialPrintBuffer
 *  prints the values from a binary char buffer in dec, bin, ascii,
 *****************************************************************************/
void serialPrintBuffer(char * buffer, int bufferSize) {
    Serial.print("binary buffer : ");
    int intVal = 0;
    for (int i = bufferSize-1; i >= 0; i--) {
        if(buffer[i] == '1') {
            Serial.print(buffer[i]);
            intVal += bit(i);
        }
        else if (buffer[i] == '0') {
            Serial.print(buffer[i]);
        }
    }
    // convert to decimal
    itoa(intVal, buffer, 10);
    Serial.print(" : DEC: ");
    Serial.print(buffer);
    // convert to binary
    itoa(intVal, buffer, 2);
    Serial.print(" : BIN: ");
    Serial.print(buffer);
    // convert to ascii
    Serial.print(" : ASCII: ");
    Serial.print(char(intVal));
    //done
    Serial.println(" : done");
    Serial.println();
}


/******************************************************************************
 *  @brief: btoi
 *  Converts char array consisting of '1's and '0's to an integer value
 *****************************************************************************/
int btoi(char * buffer, int bufferSize) {
    int intVal = 0;
    for (int i = bufferSize-1; i >= 0; i--) {
        if(buffer[i] == '1') {
            intVal += bit(i);
        }
    }
    return intVal;
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
    LaserWriter laser(laserPin, pulsePeriod-0.05*pulsePeriod); // laser has some on off time
    SensorReader sensor(sensorPin, pulsePeriod, threshold);

    // init data
    int bufferSize = 8;
    char * buffer;



    // is serving
    while(true) {
        if (Serial.available()) {
            laser.sendHeader();
            laser.readFromUser();
            delay(100); // avoid overlap
        }
        if (sensor.recvHeader()) {
            buffer = sensor.readInBuffer(bufferSize);
            serialPrintBuffer(buffer, bufferSize);
        }
    }
    return 0;
}


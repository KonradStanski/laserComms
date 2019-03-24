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
uint32_t pulsePeriod = 30; //milliseconds
int threshold = 930;


/******************************************************************************
 *  @brief: serialPrintBuffer
 *  prints the values from a binary char buffer in dec, bin, ascii,
 *****************************************************************************/
void serialPrintBuffer(char * buffer, int bufferSize) {
    Serial.print("SPrint buffer : ");
    int intVal = 0;
    for (int i = 0; i < bufferSize; i++) {
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
    // convert to ascii
    Serial.print(" : ASCII: ");
    Serial.print(char(intVal));
    //done
    Serial.println(" : done");
    Serial.println();
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

    char * buffer;
    int hamBufferSize = 14;
    // int charBufferSize = 8;
    // init data
    // little endian u IN REVERSE ORDER
    // char outBuffer[8] = {'1', '0', '1', '0', '1', '1', '1', '0'};


    // is serving
    while(true) {
        if (Serial.available()) {
            delay(60); // needed to avoid overlap of signal
            laser.sendHeader();
            // laser.readFromUser();
            char inChar = Serial.read();
            buffer = laser.charToHam(inChar);
            laser.sendBuffer(buffer, hamBufferSize);
        }
        if (sensor.recvHeader()) {
            buffer = sensor.readInBuffer(hamBufferSize);
            serialPrintBuffer(buffer, hamBufferSize);
            free(buffer);
        }
    }
    return 0;
}

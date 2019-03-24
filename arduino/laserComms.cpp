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

    // init data
    int charBufferSize = 8;
    char * buffer;


    char outBuffer[8] = {'0', '1', '1', '1', '0', '1', '0', '1'};


    // is serving
    while(true) {
        if (Serial.available()) {
            delay(60); // needed to avoid overlap of signal
            laser.sendHeader();
            // laser.readFromUser();
            Serial.read();
            laser.sendBuffer(outBuffer, charBufferSize);
        }
        if (sensor.recvHeader()) {
            buffer = sensor.readInBuffer(charBufferSize);
            serialPrintBuffer(buffer, charBufferSize);
            free(buffer);
        }
    }
    return 0;
}





// might be wrong
// /******************************************************************************
//  *  @brief: btoi
//  *  Converts char array consisting of '1's and '0's to an integer value
//  *****************************************************************************/
// int btoi(char * buffer, int bufferSize) {
//     int intVal = 0;
//     for (int i = bufferSize-1; i >= 0; i--) {
//         if(buffer[i] == '1') {
//             intVal += bit(i);
//         }
//     }
//     return intVal;
// }

// /******************************************************************************
//  *  @brief: btoi
//  *  Converts char array consisting of '1's and '0's to an integer value
//  *****************************************************************************/
// char * itob(int intVal, int bufferSize) {
//     for (int i = bufferSize-1; i >= 0; i--) {
//         if(buffer[i] == '1') {
//             intVal += bit(i);
//         }
//     }
//     return intVal;
// }


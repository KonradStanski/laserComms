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
void sendHamFromUser(LaserWriter laser, SensorReader sensor) {
    byte * buffer;
    int hamBufferSize = 14;
    char inChar = Serial.read();

    // flip a bit
    // send message
    do{
      laser.sendHeader();
      laser.sendBuffer(buffer, hamBufferSize);
      serialPrintBuffer(buffer, hamBufferSize);
      delay(60); // needed to avoid overlap of signal
    }while(!sensor.waitForAck());
    free(buffer);
}
//
// void sendHamFromUser(LaserWriter laser, SensorReader sensor) {
//   Serial.setTimeout(5000);
//     int hamBufferSize = 14;
//     String outgoingString = Serial.readStringUntil('\n');
//     char outgoing[outgoingString.length()+1];
//     strcpy(outgoing, outgoingString.c_str());
//     for(int i= 0; i < outgoingString.length()-1; i++){
//       char outchar = outgoing[i];
//       byte* buffer = laser.charToHam(outchar);
//       do{
//         laser.sendHeader();
//         laser.sendBuffer(buffer, hamBufferSize);
//         serialPrintBuffer(buffer, hamBufferSize);
//         delay(60); // needed to avoid overlap of signal
//       }while(!sensor.waitForAck());
//       free(buffer);
//     }
// }
/******************************************************************************
 *  @brief: recvHamFromUser
 *  This funciton controls the useage of the sensor class to receive hamming
    codes.
 *****************************************************************************/
void recvHamFromUser(SensorReader sensor, LaserWriter laser) {
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
    laser.sendACK();
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
            sendHamFromUser(laser, sensor);
        }
        if (sensor.recvHeader()) {
            recvHamFromUser(sensor, laser);

        }
    }
    return 0;
}

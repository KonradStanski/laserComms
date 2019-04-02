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
    //Serial.print("Print buffer : ");
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
    Serial.print(":= ");
    Serial.print(char(intVal));
    Serial.print(" [");
    Serial.print(intVal);
    Serial.print("] ");
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
    buffer = laser.charToHam(inChar);
    // flip a bit
    // send message
    do{
      laser.sendHeader();
      laser.sendBuffer(buffer, hamBufferSize);
      serialPrintBuffer(buffer, hamBufferSize);
      delay(40); // needed to avoid overlap of signal
    }while(!sensor.waitForAck());
    free(buffer);
}


/******************************************************************************
 *  @brief: sendMessage
 *  This function reads in a char buffer until a newline and then send the
    entire char buffer using hamming codes and a ack handshake
 *****************************************************************************/
void sendMessage(LaserWriter laser, SensorReader sensor) {
    String message;
    int hamBufferSize = 14;
    message = Serial.readStringUntil('\n');
    for (int i = 0; i < message.length()-1; i++) {
        int pairity = 0;
        char car = message.charAt(i);
        for(int j = 0; j < 8; j++){
          if(bitRead((int) car, i)){
            pairity |= (1 << j);
          }else pairity |= (0 << j);
        }
        byte * buffer = laser.charToHam(car);
        do{
          laser.sendHeader();
          laser.sendPair(pairity);
          laser.sendBuffer(buffer, hamBufferSize);
          serialPrintBuffer(buffer, hamBufferSize);
          delay(60); // needed to avoid overlap of signal
        }while(!sensor.waitForAck());
        free(buffer);
    }
}


/******************************************************************************
 *  @brief: recvHamFromUser
 *  This funciton controls the useage of the sensor class to receive hamming
    codes.
 *****************************************************************************/
void recvHamFromUser(SensorReader sensor, LaserWriter laser, int pairity) {
    // instanciate buffer for the hamming code and resulting char
    byte * buffer, * charBuffer;
    int hamBufferSize = 14, charBufferSize = 8, myPair;
    // read in hamming buffer

    buffer = sensor.readInBuffer(hamBufferSize);
    serialPrintBuffer(buffer, hamBufferSize);
    // convert buffer to char
    charBuffer = sensor.unHamByte(buffer);
    for(int i = 0; i < 8; i++){
      if(charBuffer[i] == 1){
        myPair ++;
      }
    }
    if(myPair == pairity){
      laser.sendACK();
      serialPrintBuffer(charBuffer, charBufferSize);
    }
    free(buffer);
    free(charBuffer);
}


// Arduino Setup Configuration
void setup() {
    init();
    Serial.begin(9600);
    Serial.setTimeout(4000);
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
            // sendHamFromUser(laser, sensor);
            sendMessage(laser, sensor);
        }
        if (sensor.recvHeader()) {
            recvHamFromUser(sensor, laser, sensor.recvPair());
        }
    }
    return 0;
}

/*# ---------------------------------------------------
#    Name: Konrad Staniszewski, Andrew Rooney
#    ID: 1531593, 1496508
#    CMPUT 275, W 2018
#    Final Project: Laser Communications
# ---------------------------------------------------*/

#include "SensorReader.h"
#include <Arduino.h>


/******************************************************************************
 *  @brief: SensorReader // constructor //
 *  Instanciate SensorReader instance
 *****************************************************************************/
SensorReader::SensorReader(char recvSensorPin, uint32_t recvPulsePeriod, int recvSensorThreshold) {
    sensorPin = recvSensorPin;
    pulsePeriod = recvPulsePeriod;
    threshold = recvSensorThreshold;
}


/******************************************************************************
 *  @brief: SensorReader // destructor //
 *  Destruc insance of SensorReader
 *****************************************************************************/
SensorReader::~SensorReader() {
}


/******************************************************************************
 *  @brief: readInBuffer
 *  reads in a char array of '1' or '0' of size bufferSize and
    returns a pointer to a char array.
    READS ARRAY IN MSB FIRST
 *****************************************************************************/
byte * SensorReader::readInBuffer(int bufferSize) {
    // init binary array
    byte *buffer = (byte*)malloc(sizeof(byte[bufferSize]));
    // fill array with binary values
    for (int i = 0; i < bufferSize; i++) {
        int lightRead = analogRead(sensorPin);
        if (lightRead > threshold) {
            buffer[i] = 1;
            delay(pulsePeriod);
        }
        else {
            buffer[i] = 0;
            delay(pulsePeriod);
        }
    }
    return buffer;
}

bool SensorReader::waitForAck(){
  int in = 0b0, out = 0b0, temp;
  for(int i = 0; i < 8; i ++){
    temp = analogRead(sensorPin);
    if (temp > threshold) {
        in = 1;
    }else in = 0;
    delay(pulsePeriod);
    out |= (in << i);
  }
  Serial.println(out);
  if(out >= 0x7){
    return stSuccess;
  }else{
    return stFail;
  }
}

/******************************************************************************
 *  @brief: recvHeader
 *  State Machine for checking if a specified header is read in. Currently is
    set to read in **0xFF**
 *****************************************************************************/
bool SensorReader::recvHeader() {
    //read in 0xFF
    // begin reading in code
    if(analogRead(sensorPin) > threshold) {
        delay(pulsePeriod/2); // delay to offset communications
        for (int i = 0; i < 2; i++) {
            if (!(analogRead(sensorPin) > threshold)) {
                // recieved 0
                return false;
            }
            else{
                // recieved 1
                delay(pulsePeriod);
            }
        }
        return true;
    }
    return false;
}

int SensorReader::recvPair(){
  int pair = 0;
     //delay(pulsePeriod/2);
    for(int i = 0; i < 3; i++){
      if(analogRead(sensorPin) > threshold){
        pair |= (1 << i);
        //Serial.println("one");
        delay(pulsePeriod);
      }else{
        //Serial.println("zeero");
        pair |= (0 << i);
        delay(pulsePeriod);
      }
    }
  return pair;
}
/******************************************************************************
 *  @brief: recvHeadSize
 *  this functin reads in a 8 bit buffer to determine the size of the data
    payload.
 *****************************************************************************/
int SensorReader::recvHeadSize() {
    // read in 8 bit integer value little endian for buffer size
    int bufferSize = 0;
    for(int i = 0; i < 8; i++) {
        if (analogRead(sensorPin) > threshold) {
            bufferSize += bit(i);
        }
        delay(pulsePeriod);
    }
    return bufferSize;
}


/******************************************************************************
 *  @brief: recvTail
 *  this function receives a tail consisting of a checksum to verify that the
    data transmission was correct.
 *****************************************************************************/
// bool SensorReader::recvTail(byte buffer[], int bufferSize) {

// }


/******************************************************************************
 *  @brief: unHamByte
 *  Accepts a byte array, and does the math as described in this
 *  https://en.wikipedia.org/wiki/Hamming(7,4) article, as suggested by Zac. This
 *  code is able to correct single bit flips. However, multiple bit flips cannot
 *  be handled here.
 *****************************************************************************/
byte* SensorReader::unHamByte(byte buffer[]){
    for(int i = 0; i < 2; i++){
        bool s1, s2, s3;
        int n=i*7, res = 0b0;
        // compute the "syndrome" values:
        s1 = (buffer[n+0])^(buffer[n+2])^(buffer[n+4])^buffer[n+6];
        s2 = (buffer[n+1])^(buffer[n+2])^(buffer[n+5])^buffer[n+6];
        s3 = (buffer[n+3])^(buffer[n+4])^(buffer[n+5])^buffer[n+6];
        res = s1 | (s2 << 1) | (s3 << 2);
        if(res){ // toggle the erroneous bit
            buffer[n+res-1] = !buffer[n+res-1];
        }
    }
    byte *outBuffer = (byte*)malloc(sizeof(byte[8]));

    outBuffer[0] = buffer[6];
    outBuffer[1] = buffer[5];
    outBuffer[2] = buffer[4];
    outBuffer[3] = buffer[2];

    outBuffer[4] = buffer[13];
    outBuffer[5] = buffer[12];
    outBuffer[6] = buffer[11];
    outBuffer[7] = buffer[9];
    return outBuffer;
}

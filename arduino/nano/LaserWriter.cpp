#include "LaserWriter.h"

// constructor
LaserWriter::LaserWriter(const int pulsePeriod){
    pulsePeriod = pulsePeriod;
    laserPin = laserPin;
}

// destructor
LaserWriter::~LaserWriter(){
}

String LaserWriter::readFromUser() {
    if (!Serial.available()) {}
    else {
        String message = Seial.readStringUntil();
        return message;
    }
    // int startTime = millis();
    // // wait for input until timeout
    // while (millis() - startTime < timeout) {
    //     if (Serial.available()) {
    //         String message = Serial.readStringUntil();
    //         return message;
    //     }
    // }
    // // timeout encountered
    // return "TIMEOUT ERROR";
}

void LaserWriter::outputMessage(String message) {

}

#include "laserWriter.h"

// constructor
laserWriter::laserWriter(){
}

// destructor
laserWriter::~laserWriter(){
}

String laserWriter::readInMessage(int timeout) {
    int startTime = millis();
    // wait for input
    if (!Serial.available()) {}
    else {
        String message = Serial.readStringUntil();
    }


}

void laserWriter::outputMessage(String message) {

}

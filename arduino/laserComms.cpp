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
char lightSensePin = A7;
int laserPin = 4;
char sensorPin = A7;
int pulsePeriod = 40;
int threshold = 600;


// Arduino Setup Configuration
void setup() {
    init();
    Serial.begin(9600);
    pinMode(lightSensePin, INPUT);
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
        // running code goes here
        // laser.readFromUser();
        sensor.readInBuffer(6);
    }
    return 0;
}
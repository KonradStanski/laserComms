#include <Arduino.h>
#include "LaserReader.h"
#include "LaserWriter.h"


char lightSensePin = A7;
int laserPin = 4;
int pulsePeriod = 40;


// Arduino Setup Configuration
void setup() {
    init();
    Serial.begin(9600);
    pinMode(lightSensePin, INPUT);
    pinMode(laserPin, OUTPUT);
    digitalWrite(laserPin, LOW);
}


int main() {
    setup();

    LaserWriter laser(pulsePeriod, laserPin);

    while(true) {
        // running code goes here
        laser.readFromUser();
    }
    return 0;
}

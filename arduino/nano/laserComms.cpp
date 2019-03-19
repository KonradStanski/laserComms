#include <Arduino.h>


char lightSensePin = A7;
int laserPin = 4;
int pulseTime = 20;


/******************************************************************************
 *  @brief: readInBuffer
 *  compute the manhattan distance between two given points.
 *****************************************************************************/
void readInBuffer( int buffSize ) {

}


/******************************************************************************
 *  @brief: printToLasert
 *  compute the manhattan distance between two given points.
 *****************************************************************************/
void printToLaser( void ) {
    if (Serial.available()) {
        char inChar = Serial.read(); // read in character
        Serial.print("typed: ");
        Serial.print(inChar);
        Serial.print(", ascii value: ");
        Serial.print((int)inChar);
        Serial.print(", ascii binary value: ");
        for (int i = 7; i >= 0; i--) {
            int bitVal = bitRead((int)inChar, i);
            Serial.print(bitVal);
            if (bitVal) {
                digitalWrite(laserPin, HIGH);
                delay(pulseTime);
                digitalWrite(laserPin, LOW);
            }
            else {
                delay(pulseTime);
            }

        }
        Serial.println(" ");
    }
}






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
    while(true) {







    }
    return 0;
}
        // // Initialize the int ascii val to 0
        // int lightRead;
        // int readVal = 0;

        // // read in 7 binary values and calculate the equivalent decimal representation
        // for (int i = 6; i >= 0; i--){
        //     lightRead = analogRead(lightSensePin); // read the pin value
        //     if (lightRead > 600) { // trigger if light is hitting the pin
        //         readVal += (int) (pow(2, i) + 0.1); // the 0.1 is added because pow returns a double that is rounded down?
        //     }
        //     delay(100);
        // }


        // Serial.print("Integer val: ");
        // Serial.print(readVal);
        // Serial.print(" Ascii Char: ");
        // Serial.println(char(readVal));
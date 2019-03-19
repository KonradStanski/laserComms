#include <Arduino.h>


char lightSensePin = A7;
int laserPin = 4;


/******************************************************************************
 *  @brief: readInBuffer
 *  reads input from the laser into a buffer
 *****************************************************************************/
void readInBuffer( int buffSize ) {
    // Initialize the int ascii val to 0
    int lightRead;
    int readVal = 0;

    // read in 7 binary values and calculate the equivalent decimal representation
    for (int i = buffSize; i >= 0; i--){
        lightRead = analogRead(lightSensePin); // read the pin value
        if (lightRead > 600) { // trigger if light is hitting the pin
            readVal += (int) (pow(2, i) + 0.1); // the 0.1 is added because pow returns a double that is rounded down?
        }
        delay(100);
    }


    Serial.print("Integer val: ");
    Serial.print(readVal);
    Serial.print(" Ascii Char: ");
    Serial.println(char(readVal));
}


/******************************************************************************
 *  @brief: printToLasert
 *  reads input from the keyboard and outputs it to the laser.
 *****************************************************************************/
void printToLaser( void ) {
    //Variable Definitions
    int pulseTime = 20;

    // wait untl
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
                // pulse a "1"
                digitalWrite(laserPin, HIGH);
                delay(pulseTime);
                digitalWrite(laserPin, LOW);
            }
            else {
                // pulse a "0"
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
        printToLaser();
    }
    return 0;
}

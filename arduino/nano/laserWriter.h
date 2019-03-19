#ifndef _LASERWRITER_H_
#define _LASERWRITER_H_

using namespace std;


// define laser related variables
const int laserPin = 8;


/******************************************************************************
 *  @brief: readInBuffer
 *  reads input from the laser into a buffer
 *****************************************************************************/
class laserWriter {
public:
    laserWriter(const int pulsePeriod); // constructor
    ~laserWriter(); // destructor

    // reads from Serial.read() until newline and returns string
    String readInMessage();
    // outputs message to laser
    void outputMessage(const String message);

private:
    int pulsePeriod;
}


#endif

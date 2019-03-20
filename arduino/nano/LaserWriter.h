#ifndef _LASERWRITER_H_
#define _LASERWRITER_H_

using namespace std;


/******************************************************************************
 *  @brief: readInBuffer
 *  reads input from the laser into a buffer
 *****************************************************************************/
class LaserWriter {
public:
    LaserWriter(const int pulsePeriod, const int laserPin); // constructor
    ~LaserWriter(); // destructor

    // reads from Serial.read() until newline and returns string
    String readFromUser();
    // outputs message to laser
    void outputMessage(const String message);

private:
    int pulsePeriod;
    int laserPin;
}

#endif

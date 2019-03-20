#ifndef _LASERREADER_H_
#define _LASERREADER_H_

#include <Arduino.h>


// define laserReader class
class laserReader {
public:
    laserReader(); // constructor
    ~laserReader(); // destructor



    readInLine();


private:
    int pulsePeriod;
};

#endif

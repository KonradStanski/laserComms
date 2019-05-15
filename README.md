# Open Air Laser Communication System

## Included Files:
```
README
/Arduino
    Makefile
    laserComms.cpp
    LaserWriter.h
    LaserWriter.cpp
    SensorReader.h
    SensorReader.cpp
```

## Requirments
1. You will need to have arduin-mk installed
2. You will need the arduino-ua library in your home folder (This is for uofa software engineering students)


## Running Instructions:
1. Wire a voltage divider from 5V to the sensor pin
2. wire the other pins as described in the wiring diagram
3. Make the project using the included makefile
4. Upload The project to your arduino


## Wiring:
```
Misc Pin <---> Arduino Pin
===========================

LASER WIRING:
GND             GND
LASER 5V        4
Sensor          A7
```




## Notes and Assumptions:
In this assignment it is assumed that the laser communication system will not incur any timing issues due to poor timing crystals from the arduino.
Usefull Links:
- http://circuit.ucsd.edu/~yhk/ece154c-spr17/pdfs/ErrorCorrectionI.pdf
- https://en.wikipedia.org/wiki/Hamming(7,4)
- http://homepages.math.uic.edu/~leon/mcs425-s08/handouts/Hamming.pdf

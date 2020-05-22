ArduinoMotionSensorExample
======================

Original work is here: https://github.com/rpicopter/ArduinoMotionSensorExample
I just made it work on ESP8622


MPU6050/MPU6500/MPU9150/MPU9250 over I2c for ESP8622

A clean example of using INV_MPU library on ESP8622. Tested on Atmega328.


Features:
- uses FastWire and I2Cdev from Jeff Rowberg
- DMP enabled
- calculates and displays gyro and quaternions
- Makefile provided for Arduino-Makefile (https://github.com/sudar/Arduino-Makefile)


When compiling please ensure one of the following is defined (see Makefile)
- #define MPU6050
- #define MPU9150
- #define MPU6500
- #define MPU9250

This has been tested using Arduino 1.0.5 libraries and a few variants of Arduino Pro Mini boards.


# Quick docs

## mympu_open(int fifo_freq)
Start communication to MPU9250
  Use 250 Hz FIFO (and DMP refresh rate). For 250Hz modified library (by github/dejanmeznarc) is needed.
  For 200 Hz use original library from github/gregd72002.

If MPU doesnt respond, restart it. (turn MPU9250 off, by disconecting Vcc); if that doesnt help check connections.
The cause for MPU9250 not responding is that Arduino/ESP8622 is restarted while recieving data form MPU9250,
so Arduino/ESP never sends ACK back to MPU; and MPU is busy waiting for ACK.


## mympu_update
 If no data is available it needs ~160 uS (ESP8622) to run and it _doesnt change_ roll/pitch/yaw values.
 If new data is available it needs ~ 1200 uS (ESP8622) to read data and it saves output to roll pitch and yaw.
    
 Error returns:
0  - success
-1 - ERROR (read error, check connections or try to turn MPU off and back on)
 1  - MPU reads requests (ACK recieved), but there is no response
 2  - returned data is
3  - MPU returns overflow bit set

## getting data
```c++
mympu.ypr[0] //yaw
mympu.ypr[1] //pitch
mympu.ypr[2] //roll

```

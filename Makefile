BOARD_TAG = atmega328
F_CPU = 8000000L
//CXXFLAGS+=-DI2CDEV_SERIAL_DEBUG 
//CXXFLAGS+=-DI2CDEV_SERIAL_DEBUG -DMPU6050 -DMPU_DEBUG 

CXXFLAGS+=-DMPU9150 

include ../Arduino-Makefile/Arduino.mk

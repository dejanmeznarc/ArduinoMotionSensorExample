#include "freeram.h"

#include "mpu.h"
#include "I2Cdev.h"

int ret;
void setup() {
  // Fastwire::setup(400,0);
  Wire.begin();
  Wire.setClock(400000);

  Serial.begin(500000);

  ret = mympu_open(250); //default 200

  Serial.print("MPU init: "); Serial.println(ret);
  Serial.print("Free mem: "); Serial.println(freeRam());

}

unsigned int c = 0; //cumulative number of successful MPU/DMP reads
unsigned int np = 0; //cumulative number of MPU/DMP reads that brought no packet back
unsigned int err_c = 0; //cumulative number of MPU/DMP reads that brought corrupted packet
unsigned int err_o = 0; //cumulative number of MPU/DMP reads that had overflow bit set



unsigned long lastRead = 0;

void loop() {
  ret = mympu_update();

  switch (ret) {
    case 0: c++; break;
    case 1: np++; return;
    case 2: err_o++; return;
    case 3: err_c++; return;
    default:
      Serial.print("READ ERROR!  ");
      Serial.println(ret);
      return;
  }


  // Serial.print(np); Serial.print("  "); Serial.print(err_c);
  Serial.print(" Y "); Serial.print(mympu.ypr[0]);
  Serial.print(" P "); Serial.print(mympu.ypr[1]);
  Serial.print(" R "); Serial.print(mympu.ypr[2]);
  //Serial.print("\tgy: "); Serial.print(mympu.gyro[0]);
  // Serial.print(" gp: "); Serial.print(mympu.gyro[1]);
  // Serial.print(" gr: "); Serial.print(mympu.gyro[2]);
  Serial.print(" t: "); Serial.println(micros() - lastRead);
  lastRead = micros();

}

#ifndef FTC_GYRO_h
#define FTC_GYRO_h

#include "FTC_ValueUtils.h"
#include "drivers/HTGYRO-driver.h"

#ifndef GYRO
#error "Gyro not defined. Define GYRO or remove Gyro library"
#endif


typedef struct
{
  float degsec;
  float deg;
  int offset;
} gyroData_t;
gyroData_t gyroData;

task gyroTask()
{
  float lastTime = nPgmTime;
  while(1)
  {
    gyroData.degsec = HTGYROreadRot(GYRO);
    gyroData.deg += dbc(gyroData.degsec, 1)*((nPgmTime-lastTime)/1000);
    lastTime = nPgmTime;
    wait1Msec(1);
  }
}

void initGyro()
{
  hogCPU();

  nxtDisplayBigTextLine(0,"Gyro");
  nxtDisplayString(2, "The gyro");
  nxtDisplayString(3,"is calibrating!");
  nxtDisplayString(5,"DO NOT MOVE THE");
  nxtDisplayString(6, " ROBOT.");

  wait1Msec(1000);

  gyroData.degsec = 0;
  gyroData.deg = 0;
  gyroData.offset = HTGYROstartCal(GYRO);

  eraseDisplay();
  releaseCPU();


  StartTask(gyroTask, 10);
}

int getGyroAngle()
{
  hogCPU();
  int local = gyroData.deg;
  releaseCPU();
  return local;
}

#endif

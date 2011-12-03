#ifndef autonoLib_h
#define autonoLib_h
#include "FTC_ValueUtils.h"
#include "FTC_PID.c"
#include "FTC_Gyro.c"


task spinnerHolder()
{
  PID c1;
  PID s2;
  initPID(c1, 2.5, 0.0001);
  crateSpinner2.target = 0;

  initPID(c2, 2.5, 0.0001);
  crateSpinner.target = 0;

  while(1)
  {
    motor[motorA] = calcPID(c1, nMotorEncoder[motorA]);
    motor[motorB] = calcPID(c2, nMotorEncoder[motorB]);
    wait1Msec(50);
  }
}

void resetEncoders()
{
  nMotorEncoder[leftDrive] = 0;
  nMotorEncoder[rightDrive] = 0;
}

void turnDegrees(int deg)
{
  PID turn;
  initPID(turn, 0.9, 0.02);
  turn.acceptedRange = 1;
  turn.target = deg;
  int cyclesStable = 0;
  while ( cyclesStable < 50 )
  {
    if ( atPIDTarget(turn) )
       cyclesStable++;
    else
      cyclesStable = 0;
    nxtDisplayString(0, "%i", turn.error);
    int output = calcPID(turn, getGyroAngle());
    motor[leftDrive] = limitVar(output, 50);
    motor[rightDrive] = -limitVar(output, 50);
  }
  motor[leftDrive] = 0;
  motor[rightDrive] = 0;
  return;
}

void driveTo(int target, int angle = -999)
{
  PID drive;
  PID _angle;

  initPID(drive, 0.19, 0.002, 0.1);
  initPID(_angle, 6.8);

  if ( angle == -999 )
  	_angle.target = getGyroAngle();
  else _angle.target = angle;

  drive.target = target;

  int cyclesStable = 0;

  while ( cyclesStable < 30 )
  {
    int out = limitVar(calcPID(drive, ((nMotorEncoder[leftDrive]-nMotorEncoder[rightDrive])/2)), 100);
    int angleOffset = limitVar(calcPID(_angle, getGyroAngle()), abs(out));

    if ( abs(drive.error) < 30 )
       cyclesStable++;
    else
      cyclesStable = 0;

    nxtDisplayString(0, "%i", out);
    nxtDisplayString(1, "%i", angleOffset);
    nxtDisplayString(2, "%i", out-angleOffset);
    nxtDisplayString(3, "%i", drive.error);

    motor[leftDrive] =  out+angleOffset;
    motor[rightDrive] = out-angleOffset;
  }

  motor[leftDrive] = 0;
  motor[rightDrive] = 0;
  return;
}

#endif

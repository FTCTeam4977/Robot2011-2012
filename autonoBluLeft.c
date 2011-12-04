#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S2,     gyro,                sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     ,                    sensorI2CCustom9V)
#pragma config(Motor,  motorA,          rightArmSpin,  tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorB,          leftArmSpin,   tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     armClaw,       tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     armWrist,      tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     ballCollector, tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     leftDrive,     tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     armBase,       tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#define GYRO S2
#include "autonoLib.c"
#include "JoystickDriver.c"

task main()
{
  initGyro();
 // waitForStart();
 // wait1Msec(2000);
  driveTo(9000); // come off the ramp
  turnDegrees(-90); // turn so we are pointed to the ball
  resetEncoders();
  driveTo(-6500, -90); // drive towards ball
  turnDegrees(-50); // angle toward ball so we can push it and end up inside the park zone
  resetEncoders();
  driveTo(-19000, -43); // drive into zone
  resetEncoders();
  driveTo(1000);
  holdSpinners();
}

#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S2,     gyro,                sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     htproto,             sensorI2CCustom9V)
#pragma config(Motor,  motorA,          rightArmSpin,  tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorB,          leftArmSpin,   tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     armClaw,       tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     armWrist,      tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     ballCollector, tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     leftDrive,     tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     armBase,       tmotorNormal, openLoop)

#define GYRO S2
#include "autonoLib.c"
#include "JoystickDriver.c"

task main()
{
  initGyro();
  //waitForStart();
  driveTo(12000);
  turnDegrees(-90);
  resetEncoders();

  driveTo(12000, -90);
  turnDegrees(0);
  resetEncoders();

  driveTo(-8000,0);
  turnDegrees(-50);
  resetEncoders();

  driveTo(-30000, 240);
  resetEncoders();
  driveTo(1000);

  holdSpinners();

  /*
  resetEncoders();
  driveTo(10000, -90);
  /*
  resetEncoders();

  driveTo(3700, -90);
  resetEncoders();

  turnDegrees(-160);
  resetEncoders();



  driveTo(8000, -160);
  turnDegrees(-240);
  resetEncoders();

  driveTo(-5000, -240);

  turnDegrees(-150);

  resetEncoders();

  driveTo(-26000, -150); // Drive across
  resetEncoders();

  driveTo(1000, -150);

  holdSpinners();


  /*driveTo(30000, -150); // Drive Back
  turnDegrees(-120);
  resetEncoders();

  driveTo(8000, -120);*/


}

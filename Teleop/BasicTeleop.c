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

#include "FTC_ValueUtils.h"

#include "drivers/HTSPB-driver.h"
#include "JoystickDriver.c"

task main()
{
  waitForStart();
  while(true)
  {
    getJoystickSettings(joystick);
    nxtDisplayString(0, "%i", ((nMotorEncoder[leftDrive]-nMotorEncoder[rightDrive])/2));
    /*
     * JS 1
     */
    motor[leftDrive] = dbc(joystick.joy1_y1,5);
    motor[rightDrive] = dbc(joystick.joy1_y2,5);
    motor[ballCollector] = (joy2Btn(2) ? -100: ( joy2Btn(3) ? 100:0));

  }
}
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

#define WRIST_EXTENDED 1000
#define WRIST_INSIDEBODY 700

#define BASE_STRAIGHTUP 322
#define BASE_PICKUP 800

#define CLAW_CLOSED 1
#define CLAW_OPEN 2
#define CLAW_DISABLED 3

#include "FTC_PID.c"
#include "FTC_ValueUtils.h"

#include "drivers/HTSPB-driver.h"
#include "JoystickDriver.c"

PID wrist; // Wrist joint
PID base; //  Base joint
PID crateSpinner; // NXT motor powered spinners on arm

int grabberTarget = CLAW_OPEN;

void armWristUpdate()
{
  int potInput = HTSPBreadADC(S3, 1, 10);
  static int loopsStable = 0;
  int maxAcceptableError;

  if ( wrist.target < 605 )
  {
    motor[armWrist] = 0;
    nxtDisplayString(6, "TFB");
    return; // Outside of safe range ( too far back )
  }
  else if ( potInput > 980 && wrist.target >= 980 )
  {
    motor[armWrist] = 0;
    nxtDisplayString(6, "TFF");
    return; // Outside of safe range ( too far forward )
  }

  if ( wrist.target < potInput ) // Going down
  {
    wrist.Kp = 0.5;
    if ( abs(wrist.error ) < 4 )
      wrist.Kd = 0;
    else
      wrist.Kd = 4;
  }
  else if ( wrist.target > potInput ) // Going up
  {
    wrist.Kp = 5;
    wrist.Kd = 1;
  }

  if ( wrist.target == WRIST_INSIDEBODY )
    maxAcceptableError = 150;
  else
    maxAcceptableError = 15;

  if ( abs(wrist.error) <= maxAcceptableError )
  {
    if ( loopsStable < 1000 ) loopsStable++; // keep it below a point so we don't go over max int size
                                             // 1000 isn't the max int size, but we shouldn't need to check any higher for this loop
  }
  else
    loopsStable = 0;

  if ( loopsStable >= 50 )
  {
    calcPID(wrist, potInput);
    wrist.errorSum = 0; // prevent I buildup
    motor[armWrist] = 0;
  }
  else
    motor[armWrist] = hlLimit(dbc(calcPID(wrist, potInput), 10), 60, -40);
}

void armBaseUpdate()
{
    int potInput = HTSPBreadADC(S3, 0, 10);
    static int loopsStable = 0;

    if ( abs(base.error) <= 20 )
    {
      if ( loopsStable < 1000 ) loopsStable++;
    }
    else
      loopsStable = 0;

    if ( potInput < 500 && potInput > 270 )
    {
      // Arm is in top range - very little force needed to maintain position
      base.Kp = 1;
      base.Ki = 0.01;
      base.errorSum = 0;
    }
    else
    {
      base.Kp = 1.5;
      base.Ki = 0.07;
    }

    if ( abs(base.error) > 750 && base.target == BASE_PICKUP ) // Arm is headed forward and we are far away
      base.Kd = 3.2; // increase D to prevent slaming against the floor
    else if ( potInput > 450 && base.target > 450 ) // TODO: check if this D modification is still needed
      base.Kd = 2.8;
    else
      base.Kd = 0.4;

    if ( loopsStable <= 20 )
      motor[armBase] = dbc(limitVar(calcPID(base, potInput), 80), 23);
    else
    {
      calcPID(base, potInput); // keep PID updated for error calculation
                               // even though we are not using it's output

      base.errorSum = 0;       // prevent I from building up
      motor[armBase] = 0;
    }
}

void armGrabberUpdate()
{
  motor[armClaw] = 0;
  return;
  if ( grabberTarget == CLAW_CLOSED && nMotorEncoder[armClaw] > 365 )
    motor[armClaw] = -50; // Slow because the tubing will pull it shut, if we go 100% it will slam
  else if ( grabberTarget == CLAW_OPEN && nMotorEncoder[armClaw] < 356 )
    motor[armClaw] = 100;
  else
    motor[armClaw] = 0;
}

#define armInRange(a,b) if ( isBetween(HTSPBreadADC(S3, 0, 10), a, b) )
#define moveSpinners(p) crateSpinner.target = p

void updateArmPosition()
{
 armInRange(1,2) moveSpinners(10);
 else armInRange(5,7) moveSpinners(300);
 else armInRange(5,7) moveSpinners(300);
 else armInRange(5,7) moveSpinners(300);
 else armInRange(5,7) moveSpinners(300);
 else armInRange(5,7) moveSpinners(300);

}

task main()
{
  initPID(base); // gains populated by update loop based on position
  base.acceptedRange = 1; // Custom I reset conditions
  base.target = HTSPBreadADC(S3, 0, 10);

  initPID(wrist, 3.5, 0.05, 8);
  wrist.acceptedRange = 1; // We impliment special checking on the wrist, prevents I reset
  wrist.target = HTSPBreadADC(S3, 1, 10);

  initPID(crateSpinner, 0.3, 0.002, 0.5);
  crateSpinner.target = 0;

  waitForStart();

  while(1)
  {
    getJoystickSettings(joystick);
    armWristUpdate();
    armBaseUpdate();

    /*
     * JS 1 - drivetrain
     */
    motor[leftDrive] = dbc(joystick.joy1_y1,5);
    motor[rightDrive] = dbc(joystick.joy1_y2,5);

    /*
     * JS 2 - arm
     */
    if ( joy1Btn(2) )
      base.target = BASE_STRAIGHTUP;
    else if ( joy1Btn(3) )
      base.target = BASE_PICKUP;

    // Update outputs
    armWristUpdate();
    armBaseUpdate();

  }
}

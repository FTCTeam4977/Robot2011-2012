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

#define WRIST_EXTENDED 810
#define WRIST_INSIDEBODY 570

#define BASE_BACK 263
#define BASE_STRAIGHTUP 356
#define BASE_PICKUP 780
#define BASE_TWOSTACK 698
#define BASE_THREESTACK 550
#define BASE_FOURSTACK 450

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
PID crateSpinner2; // Other crate spinner... possobly move this to an array in the future

int grabberTarget = CLAW_OPEN;

void armWristUpdate()
{
  int potInput = HTSPBreadADC(S3, 1, 10);
  static int loopsStable = 0;
  int maxAcceptableError;

  if ( wrist.target < 500 )
  {
    motor[armWrist] = 0;
    //nxtDisplayString(6, "TFB");
    return; // Outside of safe range ( too far back )
  }
  else if ( potInput > 980 && wrist.target >= 980 )
  {
    motor[armWrist] = 0;
    //nxtDisplayString(6, "TFF");
    return; // Outside of safe range ( too far forward )
  }

  if ( wrist.target < potInput ) // Going down
  {
    wrist.Kp = 0.5;
    if ( abs(wrist.error ) < 10 )
      wrist.Kd = 0;
    else
      wrist.Kd = 3.3;
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
    motor[armWrist] = hlLimit(dbc(calcPID(wrist, potInput), 10), 95, (wrist.target < potInput&&abs(wrist.error) < 20 ? -20:-40));
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
      base.Kp = 0.7;
      base.Ki = 0.01;
      base.errorSum = 0;
    }
    else
    {
      base.Kp = 1.5;
      base.Ki = 0.07;
    }

    if ( abs(base.error) > 70 && base.target == BASE_PICKUP ) // Arm is headed forward and we are far away
      base.Kd = 2.5; // increase D to prevent slaming against the floor
    //else if ( potInput > 450 && base.target > 450 ) // TODO: check if this D modification is still needed
    //  base.Kd = 2.5;
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

int crateRawTarget = 0;
int crateManualControlOffset = 0;

#define armInRange(a,b) if ( isBetween(HTSPBreadADC(S3, 0, 10), a, b) )
#define wristInRange(a,b) if ( isBetween(HTSPBreadADC(S3, 1, 10), a, b) )

void moveSpinners(int p)
{
  crateRawTarget = p;
  crateSpinner.target = (crateRawTarget+crateManualControlOffset);
  crateSpinner2.target = (crateRawTarget+crateManualControlOffset);
}

void updateCratePosition()
{
  if ( abs(wrist.error) < 50 && wrist.target == WRIST_EXTENDED ) // Normal ( picking up crates, etc )
  {
    //moveSpinners((-40/233)*HTSPBreadADC(S3, 0, 10)+140.0858369);
    armInRange(701, 900) moveSpinners(0);
    else armInRange(650, 700) moveSpinners(6);
    else armInRange(559,733) moveSpinners(30);
    else armInRange(558, 400) moveSpinners(50);
    else armInRange(400, 300) moveSpinners(80);
  }
  else if ( abs(wrist.error) > 30 && wrist.target == WRIST_EXTENDED ) // Wrist is moving to top, needs to stay level
  {
    //wristInRange(700, 1024) moveSpinners(170);
     wristInRange(650, 1024) moveSpinners(90); // top
     //else wristInRange(670, 800) moveSpinners(
     else wristInRange(650, 600) moveSpinners(200); // mid range
     else wristInRange(400, 600) moveSpinners(250); // pulling out
  }
  else if ( wrist.target == WRIST_INSIDEBODY ) // Wrist is moving back, crate is empty so don't bother keeping level
    moveSpinners(340);

  //nxtDisplayString(1, "%i", HTSPBreadADC(S3, 1, 10));
  motor[motorA] = calcPID(crateSpinner, nMotorEncoder[motorA]);
  motor[motorB] = calcPID(crateSpinner2, nMotorEncoder[motorB]);
}

void armGrabberUpdate()
{
  static long timeRef = nPgmTime;
  static int lastTarget = grabberTarget;

  if ( lastTarget != grabberTarget )
    timeRef = nPgmTime+300;

  if ( grabberTarget == CLAW_OPEN && timeRef > nPgmTime )
    motor[armClaw] = 80;
  else if ( grabberTarget == CLAW_CLOSED && timeRef > nPgmTime  )
    motor[armClaw] = -50;
  else
    motor[armClaw] = 0;

  lastTarget = grabberTarget;
}



task main()
{
  nMotorEncoder[motorA] = -42;
  nMotorEncoder[motorB] = -42;


  initPID(base); // gains populated by update loop based on position
  base.acceptedRange = 1; // Custom I reset conditions
  base.target = HTSPBreadADC(S3, 0, 10);

  initPID(wrist, 3.5, 0.05, 8);
  wrist.acceptedRange = 1; // We impliment special checking on the wrist, prevents I reset

  initPID(crateSpinner2, 2.1);
  crateSpinner2.target = -42;

  initPID(crateSpinner, 2.4);
  crateSpinner.target = -42;

  wrist.target = HTSPBreadADC(S3, 1, 10);

  waitForStart();
  base.target = HTSPBreadADC(S3, 0, 10);
  wrist.target = HTSPBreadADC(S3, 1, 10);

  grabberTarget = CLAW_CLOSED;
  bDisplayDiagnostics = true;
  while(1)
  {
    nxtDisplayString(0,"%i %i",nMotorEncoder[motorA], HTSPBreadADC(S3, 1, 10));

    getJoystickSettings(joystick);
    /*
     * JS 1 - drivetrain
     */
    motor[leftDrive] = dbc(joystick.joy1_y1,15);
    motor[rightDrive] = dbc(joystick.joy1_y2,15);
    /*
     * JS 2 - arm
     */

    // Arm positioning
    if ( joy2Btn(1) && wrist.target != WRIST_INSIDEBODY )
      base.target = BASE_PICKUP;
    else if ( joy2Btn(2) && wrist.target != WRIST_INSIDEBODY )
      base.target = BASE_TWOSTACK;
    else if ( joy2Btn(3) && wrist.target != WRIST_INSIDEBODY )
      base.target = BASE_THREESTACK;
    else if ( joy2Btn(4) && wrist.target != WRIST_INSIDEBODY )
      base.target = BASE_FOURSTACK;
    else if ( joy2Btn(10) ) // crate up / store up
    {
      base.target = BASE_STRAIGHTUP;
      wrist.target = WRIST_EXTENDED;
    }
    else if ( joy2Btn(9) && base.target == BASE_STRAIGHTUP ) // crate inside
    {
      wrist.target = WRIST_INSIDEBODY;
      base.target = 263;
      grabberTarget = CLAW_CLOSED;
    }

    // Claw grab toggle
    if ( joy2Btn(6) )
      grabberTarget = CLAW_CLOSED;
    else if ( joy2Btn(5) && wrist.target != WRIST_INSIDEBODY )
    {
      crateManualControlOffset = 0;
      grabberTarget = CLAW_OPEN;
    }

    // Crate offset manual reset
    /*if ( joy2Btn(11) )
      crateManualControlOffset = 0;*/

    if ( dbc(joystick.joy2_y1, 5) != 0 )
    {
      motor[motorA] = joystick.joy2_y1/1.8;
      motor[motorB] = joystick.joy2_y1/1.8;
      crateManualControlOffset = nMotorEncoder[motorA]-crateRawTarget;
    }
    else
      updateCratePosition();

    motor[ballCollector] = (joy2Btn(7) ? -100:(joy2Btn(8)?100:-30));

    // Update outputs
    armWristUpdate();
    armBaseUpdate();
    armGrabberUpdate();
  }
}


void BluLeft()
{
  initGyro();
  waitForStart();
  wait1Msec(2000);
  driveTo(10500); // come off the ramp
  turnDegrees(-90); // turn so we are pointed to the ball
  resetEncoders();
  driveTo(-5000, -90); // drive towards ball
  turnDegrees(-50); // angle toward ball so we can push it and end up inside the park zone
  resetEncoders();
  driveTo(-19000, -43); // drive into zone
  while(1);
    
}

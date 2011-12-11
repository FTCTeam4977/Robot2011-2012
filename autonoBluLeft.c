
void BluLeftBall()
{
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

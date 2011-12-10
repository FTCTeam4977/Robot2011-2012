
void RedRightBall()
{
  //turnDegrees(-30);
  driveTo(9000, 0);
  turnDegrees(90);
  resetEncoders();
  driveTo(-6500, 90);
  turnDegrees(70);
  resetEncoders();
  driveTo(-18000, 67);
  holdSpinners();
}


void RedLeftBall()
{
  driveTo(10000);
  turnDegrees(90);
  resetEncoders();
  driveTo(-4000, 90);
  turnDegrees(60);
  resetEncoders();
  driveTo(-18000, 60);
  resetEncoders();
  driveTo(500);
  holdSpinners();
}

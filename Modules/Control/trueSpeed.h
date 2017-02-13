#ifndef BCI_TRUESPEED_H_INCLUDED
#define BCI_TRUESPEED_H_INCLUDED

const unsigned int BCI_TrueSpeed[128] =
{
  0, 17, 18, 18, 18, 19, 19, 19, 20, 20,
 20, 21, 21, 21, 22, 22, 22, 23, 24, 24,
 25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
 28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
 33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
 37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
 41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
 46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
 52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
 61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
 71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
 80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
 88, 89, 89, 90, 90,127,127,127
};

#define BCI_GetTrueSpeed(val) ( BCI_TrueSpeed[abs(val)] * sgn(val) )

#ifdef BCI_USE_CUSTOM_TRUESPEED
  /**
   * Measures the trueSpeed for your robot, which will be a better LUT than the
   * included one. This code assumes that sending a positive signal to the motors
   * causes the robot to drive forward, causing the quadrature encoderse to count
   * in the positive direction. This code also assumes that there are no gear
   * ratios between the motors and the quadrature encoders (i.e., that the gear
   * ratio is 1:1). This function will drive your robot forward and backward for,
   * 3 seconds each time iteratively calculating the LUT, and printing a
   * delta-improvement percentage and the new LUT to the debug stream each
   * iteration. Be sure you have enough space for the robot to move around in,
   * Stop the program and record the LUT when you are satisfied
   * @param leftMotors  Array of left drive motors
   * @param leftLen     Length of that array
   * @param rightMotors Array of right drive motors
   * @param rightLen    Length of that array
   * @param leftQuad    Left quadrature encoder
   * @param rightQuad   Right quadrature encoder
   */
  void trueSpeed_Measure(tMotor *leftMotors, const int leftLen, tMotor *rightMotors, const int rightLen, tSensors leftQuad, tSensors rightQuad);
#endif //BCI_USE_CUSTOM_TRUESPEED
#endif //BCI_TRUESPEED_H_INCLUDED

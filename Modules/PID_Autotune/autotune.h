#ifndef BCI_AUTOTUNE_H_INCLUDED
#define BCI_AUTOTUNE_H_INCLUDED

/**
 * Autotunes for a pos_PID controller.
 * @param leftMotors     Array of left motors
 * @param numLeftMotors  Number of left motors
 * @param rightMotors    Array of right motors
 * @param numRightMotors Number of right motors
 * @param leftQuad       Left quadrature encoder
 * @param rightQuad      Right quadrature encoder
 * @param target         Target to tune for
 */
void autotune_Run(tMotor *leftMotors, const int numLeftMotors, tMotor *rightMotors, const int numRightMotors, const tSensors leftQuad, const tSensors rightQuad, const long target);

#endif //BCI_AUTOTUNE_H_INCLUDED

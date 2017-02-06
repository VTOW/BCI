#ifndef BCI_ODOMETRY_H_INCLUDED
#define BCI_ODOMETRY_H_INCLUDED

//This code is based off of the work of Griffin Tabor

struct bci_odom_t
{
  long pos_x, pos_y, pos_theta;

  float scaleFactor;
  tSensors leftQuad, rightQuad;
};

static struct bci_odom_t bci_internal_odom;

//This is the output of the task
long BCI_Odometry_X, BCI_Odometry_Y, BCI_Odometry_Theta;

/**
 * Initializes the odometry data. All lengths are in millimeters and all
 * rotations are in degrees.
 * @param leftQuad    Left quad encoder
 * @param rightQuad   Right quad encoder
 * @param start_x     Starting x coordinate (mm)
 * @param start_y     Starting y coordinate (mm)
 * @param start_theta Starting theta rotation (deg)
 * @param scaleFactor Conversion between encoder ticks and millimeters. The
 * default value for this is for 4" omni wheels.
 */
void odometry_Initialize(const tSensors leftQuad, const tSensors rightQuad, const long start_x, const long start_y, const long start_theta, const float scaleFactor = 9.2345);

/**
 * Takes a guess at calculating your scale factor. This will never be as
 * accurate as experimentally determining it yourself.
 * @param chassisDiameter Diameter of chassis in inches
 * @param wheelDiameter   Diameter of wheel in inches
 */
void odometry_GuessScaleFactor(const float chassisDiameter, const float wheelDiameter);

/**
 * Tracks the realtime odometry of the robot and produces a global position
 * estimate written to the globals above. THIS TASK CLEARS THE QUAD ENCODERS
 * YOU SUPPLY! DO NOT WRITE TO THE VALUES OF THE QUADS ENCODERS! If you change
 * the values of the quad encoders yourself, your position estimate will be
 * completely wrong. Instead of clearing them, save their value and go from
 * there.
 */
task trackOdometry();

#endif //BCI_ODOMETRY_H_INCLUDED

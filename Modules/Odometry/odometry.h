#ifndef BCI_ODOMETRY_H_INCLUDED
#define BCI_ODOMETRY_H_INCLUDED

//This code is based off of the work of Griffin Tabor

struct bci_odom_t
{
  long pos_x, pos_y, pos_theta;

  float scale, turnScale;
  tSensors leftQuad, rightQuad;
};

static struct bci_odom_t bci_internal_odom;

//This is the output of the trackOdometry task
long BCI_Odometry_X, BCI_Odometry_Y, BCI_Odometry_Theta;

/**
 * Initializes the odometry data. All lengths are in millimeters and all
 * rotations are in degrees.
 * @param leftQuad    Left quad encoder
 * @param rightQuad   Right quad encoder
 * @param start_x     Starting x coordinate (mm)
 * @param start_y     Starting y coordinate (mm)
 * @param start_theta Starting theta rotation (deg)
 */
void odom_Initialize(const tSensors leftQuad, const tSensors rightQuad, const long start_x, const long start_y, const long start_theta);

/**
 * Sets the scale and turn scale for the odometry task.
 * @param scale       Conversion between encoder ticks and millimeters.
 * @param turnScale   Conversion between encoder tick difference and degrees.
 */
void odom_SetScales(const float scale, const float turnScale);

/**
 * Takes a guess at calculating your scale and turning scale. This will never be
 * as accurate as experimentally determining it yourself.
 * @param chassisDiameter Diameter of wheel base in inches
 * @param wheelDiameter   Diameter of wheel in inches
 */
void odom_GuessScales(const float chassisDiameter, const float wheelDiameter, const float ticksPerRev = UTIL_QUAD_TPR);

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

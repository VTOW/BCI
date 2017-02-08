#ifndef BCI_POINTMATH_H_INCLUDED
#define BCI_POINTMATH_H_INCLUDED

typedef struct distanceAndAngle_t
{
	float length;
	float theta;
} distanceAndAngle;

/**
 * Computes the distance to a point
 * @param  x X coordinate of point
 * @param  y Y coordinate of point
 * @return   Distance to point in mm
 */
float pm_computeDistanceToPoint(const long x, const long y);

/**
 * Computes the angle to a point
 * @param  x X coordinate of point
 * @param  y Y coordinate of point
 * @return   Angle to point in degrees
 */
float pm_computeAngleToPoint(const long x, const long y);

/**
 * Computes the disdistance and angle to a point
 * @param x   X coordinate of point
 * @param y   Y coordinate of point
 * @param out Struct for result
 */
void pm_computeDistanceAndAngleToPoint(const long x, const long y, distanceAndAngle *out);

#endif //BCI_POINTMATH_H_INCLUDED

#ifndef BCI_POINTMATH_C_INCLUDED
#define BCI_POINTMATH_C_INCLUDED

#include "pointMath.h"

float pm_computeDistanceToPoint(const long x, const long y)
{
	//Compute difference in distance
	const float xDiff = x - bci_internal_odom.pos_x, yDiff = y - bci_internal_odom.pos_y;
	return sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

float pm_computeAngleToPoint(const long x, const long y)
{
	//Compute difference in distance
	const float xDiff = x - bci_internal_odom.pos_x, yDiff = y - bci_internal_odom.pos_x.pos_y;

	//Compute difference in angle
	return (atan2(yDiff, xDiff) * (180 / PI)) - bci_internal_odom.pos_theta;
}

void pm_computeDistanceAndAngleToPoint(const long x, const long y, distanceAndAngle *out)
{
	const float xDiff = x - bci_internal_odom.pos_x, yDiff = y - bci_internal_odom.pos_y;
	out->length = sqrt((xDiff * xDiff) + (yDiff * yDiff));

	//Compute difference in angle
	out->theta = (atan2(yDiff, xDiff) * (180 / PI)) - bci_internal_odom.pos_theta;
}

#endif //BCI_POINTMATH_C_INCLUDED

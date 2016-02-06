#ifndef VECTOR3F_C_INCLUDED
#define VECTOR3F_C_INCLUDED

#ifndef VECTOR3F_H_INCLUDED
#include "vector3f.h"
#endif

/*
* Returns the length of a vector
*/
float vector3f_Length(const vector3f* v)
{
	return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

/*
* Returns the dot product of a vector
*/
float vector3f_Dot(const vector3f* v)
{
	return v->x * v->x + v->y * v->y + v->z * v->z;
}

/*
* Returns the cross product of two vectors
*/
vector3f* vector3f_Cross(const vector3f* v1, const vector3f* v2)
{
	vector3f *vOut;

	vOut->x = v1->y * v2->z - v1->z * v2->y;
	vOut->y = v1->z * v2->x - v1->z * v2->z;
	vOut->z = v1->x * v2->y - v1->y * v2->x;

	return vOut;
}

/*
* Returns a normalized vector
*/
vector3f* vector3f_Normalize(const vector3f* v)
{
	vector3f *vOut;

	float length = vector3f_Length(v);

	vOut->x = v->x / length;
	vOut->y = v->y / length;
	vOut->z = v->z / length;

	return vOut;
}

#endif //#ifndef VECTOR3F_C_INCLUDED

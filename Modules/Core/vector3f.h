#ifndef VECTOR3F_H_INCLUDED
#define VECTOR3F_H_INCLUDED

typedef struct vector3f
{
	float x, y, z;
} vector3f;

//Returns the length of a vector
float vector3f_Length(const vector3f* v);

//Returns the dot product a vector
float vector3f_Dot(const vector3f* v);

//Returns the cross product of two vectors
vector3f* vector3f_Cross(const vector3f* v1, const vector3f* v2);

//Returns a normalized vector
vector3f* vector3f_Normalize(const vector3f* v);

#endif //#ifndef VECTOR3F_H_INCLUDED

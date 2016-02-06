#ifndef VECTOR2F_H_INCLUDED
#define VECTOR2F_H_INCLUDED

typedef struct vector2f
{
	float x, y;
} vector2f;

//Vector length
float vector2f_length(vector2f *v);

//Vector rotation relative to x axis (positive direction)
float vector2f_rotation(vector2f *v);

#endif //VECTOR2F_H_INCLUDED

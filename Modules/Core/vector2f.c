#ifndef VECTOR2F_C_INCLUDED
#define VECTOR2F_C_INCLUDED

#include "vector2f.h"

float vector2f_length(vector2f *v)
{
	return sqrt(v->x * v->x + v->y * v->y);
}

float vector2f_rotation(vector2f *v)
{

}

#endif //VECTOR2F_C_INCLUDED

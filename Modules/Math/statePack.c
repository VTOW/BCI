#ifndef BCI_STATEPACK_C_INCLUDED
#define BCI_STATEPACK_C_INCLUDED

#include "statePack.h"

void sp_Translate(statePack *sp, const int dist, const int angle)
{
  sp->x += cosDegrees(angle) * dist;
  sp->y += sinDegrees(angle) * dist;
}

void sp_Rotate(statePack *sp, const int angle)
{
  sp->theta += angle;
}

void sp_Rotate_Point(statePack *sp, const int angle, const long x, const long y)
{
  sp->x = sp->x + (x - sp->x) * cosDegrees(angle) - (y - sp->y) * sinDegrees(angle);
  sp->y = sp->y + (x - sp->x) * sinDegrees(angle) - (y - sp->y) * cosDegrees(angle);
}

#endif //BCI_STATEPACK_C_INCLUDED

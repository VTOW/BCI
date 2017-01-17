#ifndef BCI_STATEPACK_H_INCLUDED
#define BCI_STATEPACK_H_INCLUDED

typedef struct statePack_t
{
  long x, y, theta;
} statePack;

/**
 * Translates this SP
 * @param sp    SP to translate
 * @param dist  Length to translate
 * @param angle Angle for translation (degrees) (specified in global frame)
 */
void sp_Translate(statePack *sp, const int dist, const int angle);

/**
 * Rotates this SP
 * @param sp    SP to rotate
 * @param angle Angle to rotate by (degrees)
 */
void sp_Rotate(statePack *sp, const int angle);

/**
 * Rotates this SP around a point
 * @param sp    SP to rotate
 * @param angle Angle to rotate by (degrees)
 * @param x     X coordinate
 * @param y     Y coordinate
 */
void sp_Rotate_Point(statePack *sp, const int angle, const long x, const long y);

#endif //BCI_STATEPACK_H_INCLUDED

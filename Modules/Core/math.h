#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

/***************************************************************************/
/*                                                                         */
/* Math definitions                                                        */
/*                                                                         */
/***************************************************************************/
#define CUBED_127 16129
#define ROOT_2    1.414
#define EPSILON   1000
#define sign(value) ( (value) >= 0 ? 1 : (-1) )
#define cube(value) ( (value) * (value) * (value) )
#define inchesToTicks(inches, diam) ( ((inches) / (PI * (diam))) * 360 )
#define ticksToInches(ticks, diam) ( ((diam) * PI) * ((ticks) / 360) )

#endif //#ifndef MATH_H_INCLUDED

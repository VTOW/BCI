#define BCI_USE_ODOMETRY
#include "..\..\BCI.h"

task main()
{
  //Initialize odometry to run off of our left and right quadrature encoders
  //and assume we start at exactly position (0,0) and rotation 0
  odometry_Initialize(leftQuad, rightQuad, 0, 0, 0);

  //Guess the scales for our robot. Our wheel base is 17.5 inches and we are
  //using 4 inch omni wheels. Note: This will never be as good as determining
  //thse numbers yourself experimentally and calling odometry_SetScales instead
  odometry_GuessScales(17.5, 4);

  //Start the odometry task. From this point onward, we are not allowed to
  //modify the values of the quadrature encoders we passed in earlier
  startTask(trackOdometry);

  while (BCI_Odometry_X < 100)
  {
    //Drive along x for 100 mm
  }

  while (BCI_Odometry_Theta < 90)
  {
    //Turn 90 deg
  }

  while (BCI_Odometry_Y < 100)
  {
    //Drive along y for 100 mm
  }
}

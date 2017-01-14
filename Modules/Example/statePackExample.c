#include "..\..\BCI.h"

task main()
{
	clearDebugStream();

  statePack sp;

  sp.x = 0;
  sp.y = 0;
  sp.theta = 0;

  sp_Translate(&sp, 10, 45);
  sp_Rotate(&sp, 90);
  sp_Translate(&sp, -7, 0);

  writeDebugStreamLine("x: %d, y: %d, theta: %d", sp.x, sp.y, sp.theta);
}

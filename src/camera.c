#include "global.h"
// camera for ship zoom 
 int camera(SHIP ship, GLfloat distance){
  gluLookAt(						/* Point the camera as follows */
  -ship.x - (float)sin(ship.rot*degtorad)*distance,	/* Look from a Distance */
  ship.y + 3,						/* Look from above */
  -ship.z - (float)cos(ship.rot*degtorad)*distance,	/* Look from a Distance */
  -ship.x + (float)sin(ship.rot*degtorad)*100,		/* Move Ship to Bottom of Screen */
  ship.y,						/* Look at Ship Height*/
  -ship.z + (float)cos(ship.rot*degtorad)*100,		/* Move Ship to Bottom of Screen */
   0,1,0						/* Up Vector */
  );
  
  return 1;
}

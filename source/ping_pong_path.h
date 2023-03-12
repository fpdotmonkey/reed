#ifndef __REED_PING_PONG_PATH_H__
#define __REED_PING_PONG_PATH_H__

#include "numbers.h"

namespace reed {

/**
  A simple curve to fill the area of a rectangle

  It goes back and forth across the rectangle's x dimension,
  incrementing by @c pitch in the y direction every time it hits a wall
  until it reached the end of the rectangle.
*/
Path
ping_pong_path(Rectangle field, Millimeter pitch);

}

#endif // __REED_PING_PONG_PATH_H__

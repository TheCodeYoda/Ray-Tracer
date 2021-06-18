#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

class ray {
 public:
  point3 origin;
  vec3 direction;

 public:
  /* Ray equation: P(t) = A + tb
     A ----> origin
     b ----> direction
     t ----> time */

  /* ctors */
  ray(){};

  ray(point3 origin, vec3 direction)
  {
    this->origin = origin;
    this->direction = direction;
  }

  /* given t value tells which coordinate ray is at from the ray eqn*/
  point3 at(double t)
  {
    return this->origin + t * this->direction;
  }
};
#endif

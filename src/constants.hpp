#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

/* Usings */

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

/* Constants */

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

/* Utility functions */

inline double degrees_to_radians(double degrees)
{
  return degrees * pi / 180.0;
}

/* clamping for antialiasing and ray_color fxn */
inline double clamp(double x, double min, double max)
{
  if (x < min)
    return min;
  if (x > max)
    return max;
  return x;
}

/* random functions */
inline double random_double()
{
  /* Returns a random real in [0,1). */
  return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
  /* Returns a random real in [min,max). */
  return min + (max - min) * random_double();
}
/* Frequently used headers */
#endif

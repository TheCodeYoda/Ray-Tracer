#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <limits>
#include <memory>

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

/* Frequently used headers */

#include "ray.hpp"
#include "vec3.hpp"

#endif

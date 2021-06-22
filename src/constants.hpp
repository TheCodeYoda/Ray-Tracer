#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>

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
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

/* Frequently used headers */

#include "ray.hpp"
#include "vec3.hpp"

#endif

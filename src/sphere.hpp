#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.hpp"
#include "ray.hpp"

class sphere {
 public:
  point3 center;
  double radius;

 public:
  /* ctors */
  sphere()
  {
    this->center = {0, 0, 0};
    this->radius = 1.0;
  }

  sphere(point3 center, double radius)
  {
    this->center = center;
    this->radius = radius;
  }

  /* returns time at which ray hits the sphere else returns -1.0 */
  double hit(const ray &r)
  {
    auto direction = r.direction;
    auto origin = r.origin;
    auto oc = origin - center;

    /* quadratic eqn ax^2 + bx + c = 0 */
    /* discrimant = b^2 - 4ac */

    auto a = direction.dot(direction);
    auto b = 2 * (direction.dot(oc));
    auto c = oc.dot(oc) - (radius * radius);

    auto discriminant = (b * b) - (4 * a * c);
    if (discriminant > 0) {
      /* returns a single root */
      return (-b + sqrt(discriminant)) / (2 * a);
    }
    return -1.0;
  }
};

#endif

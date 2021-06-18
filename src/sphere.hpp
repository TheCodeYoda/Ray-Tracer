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

  bool hit(const ray &r)
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
    return (discriminant > 0);
  }
};

#endif

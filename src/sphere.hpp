#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.hpp"
#include "ray.hpp"
#include "hittable.hpp"

class sphere : public hittable {
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

  virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec);
};

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec)
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
    auto root = (-b + sqrt(discriminant)) / (2 * a);
    if (root >= t_min && root <= t_max) {
      rec.t = root;
      /* point of intersection on sphere */
      rec.p = r.at(root);
      auto outward_normal = (rec.p - this->center) / radius;
      rec.set_face_normal(r, outward_normal);
      return true;
    }
  }
  return false;
}

#endif

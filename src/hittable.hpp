#ifndef HITTABLE_H
#define HITTABLE_H
#include "vec3.hpp"
#include "ray.hpp"

struct hit_record {
  point3 p;
  vec3 normal;
  double t;
};

/* abstract class */
class hittable {
  virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) = 0;
};

#endif

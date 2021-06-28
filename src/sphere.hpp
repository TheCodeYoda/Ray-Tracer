#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.hpp"
#include "ray.hpp"
#include "hittable.hpp"
#include "material.hpp"

class sphere : public hittable {
 public:
  point3 center;
  double radius;
  shared_ptr<material> mat_ptr;

 public:
  /* ctors */
  sphere()
  {
    this->center = {0, 0, 0};
    this->radius = 1.0;
  }

  sphere(point3 center, double radius, shared_ptr<material> mptr)
  {
    this->center = center;
    this->radius = radius;
    this->mat_ptr = mptr;
  }

  virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
};

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
  vec3 oc = r.origin - center;
  auto a = r.direction.length_square();
  auto half_b = oc.dot(r.direction);
  auto c = oc.length_square() - radius * radius;

  auto discriminant = half_b * half_b - a * c;
  if (discriminant < 0)
    return false;
  auto sqrtd = sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  auto root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || t_max < root)
      return false;
  }

  rec.t = root;
  rec.p = r.at(root);
  vec3 outward_normal = (rec.p - center) / radius;
  rec.set_face_normal(r, outward_normal);
  rec.mat_ptr = mat_ptr;
  return true;
}

#endif

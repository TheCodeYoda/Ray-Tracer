#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "constants.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "hittable.hpp"
#include "material.hpp"
#include <memory>

class triangle : public hittable {
 public:
  point3 p1;
  point3 p2;
  point3 p3;
  shared_ptr<material> mat_ptr;

 public:
  triangle(point3 p1, point3 p2, point3 p3, shared_ptr<material> mat_ptr)
  {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->mat_ptr = mat_ptr;
  }

  virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
};

bool triangle::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
  vec3 edge1 = p2 - p1;
  vec3 edge2 = p3 - p2;
  vec3 edge3 = p3 - p1;

  auto normal = edge1.cross(edge2);

  /* ray is parallel to triangle */
  if (normal.dot(r.direction) == 0) {
    return false;
  }

  /* dist -> gives distance between origin and plane(perpendicular distance) */
  auto dist = normal.dot(p1);
  /* Ax + By + Cz + D = 0 */
  /* P = O + tR  after substi this in above eqn and solving for t we get the below expression*/
  double t = -(normal.dot(r.origin) + dist) / normal.dot(r.direction);
  /* check if triangle is behind the ray */
  if (t < 0) {
    return false;
  }
  point3 poi = r.at(t);

  /* check is poi is inside triangle or not */
  vec3 edge1_cross = edge1.cross(poi);
  vec3 edge2_cross = edge2.cross(poi);
  vec3 edge3_cross = edge3.cross(poi);
  if (normal.dot(edge1) < 0 || normal.dot(edge2) < 0 || normal.dot(edge3) < 0) {
    return false;
  }
  rec.t = t;
  rec.p = poi;
  rec.mat_ptr = mat_ptr;
  rec.set_face_normal(r, normal);
  return true;
}

#endif

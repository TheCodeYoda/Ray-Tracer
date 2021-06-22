#ifndef HITTABLE_H
#define HITTABLE_H
#include "vec3.hpp"
#include "ray.hpp"

struct hit_record {
  point3 p;
  vec3 normal;
  double t;
  bool front_face;

  void set_face(const ray &r, const vec3 &outward_normal)
  {
    /* to determine whether ray hit front face or back face we can check if ray and normal are in
     * same direction */
    /* ray and normal same direction ---> dot prod +ve back_face ray coming from inside */
    /*  ray and normal opp direction ---> dot prod -ve front_face ray coming from outside */
    this->front_face = (r.direction.dot(outward_normal)) < 0;
    this->normal = front_face ? outward_normal : -outward_normal;
  }
};

/* abstract class */
class hittable {
 public:
  virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) = 0;
};

#endif

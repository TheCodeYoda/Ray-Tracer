#ifndef MATERIAL_H
#define MATERIAL_H

#include "constants.hpp"

struct hit_record;

/* abstract class to model scattering which will be overridden accordingly */

/* For our program the material needs to do two things: */

/*     1)  Produce a scattered ray (or say it absorbed the incident ray). */
/*     2) If scattered, say how much the ray should be attenuated. */

class material {
 public:
  virtual bool scatter(const ray &ray_in,
                       const hit_record &rec,
                       color &attenuation,
                       ray &scattered) const = 0;
};

class lambertian : public material {
 public:
  color albedo;

 public:
  lambertian(const color &c)
  {
    this->albedo = c;
  }
  virtual bool scatter(const ray &ray_in,
                       const hit_record &rec,
                       color &attenuation,
                       ray &scattered) const override
  {
    auto scatter_direction = rec.normal + random_unit_vector();

    /* catch degenerate scattered rays */
    if (scatter_direction.near_zero()) {
      scatter_direction = rec.normal;
    }

    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }
};

class metal : public material {
 public:
  color albedo;

 public:
  metal(const color &c)
  {
    this->albedo = c;
  }
  virtual bool scatter(const ray &ray_in,
                       const hit_record &rec,
                       color &attenuation,
                       ray &scattered) const override
  {
    vec3 reflected = reflect(unit_vector(ray_in.direction), rec.normal);
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return (scattered.direction.dot(rec.normal) > 0);
    return true;
  }
};

#endif

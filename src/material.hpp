#ifndef MATERIAL_H
#define MATERIAL_H

#include "constants.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include "hittable.hpp"

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
  double fuzz; /* reflection has a small random factor as spheres get larger*/

 public:
  metal(const color &c, double fuzz)
  {
    this->albedo = c;
    this->fuzz = fuzz;
  }
  virtual bool scatter(const ray &ray_in,
                       const hit_record &rec,
                       color &attenuation,
                       ray &scattered) const override
  {
    vec3 reflected = reflect(unit_vector(ray_in.direction), rec.normal);
    scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo;
    return (scattered.direction.dot(rec.normal) > 0);
    return true;
  }
};

class dielectric : public material {
 public:
  double index_of_refraction;

 public:
  dielectric(double ir)
  {
    this->index_of_refraction = ir;
  }
  virtual bool scatter(const ray &ray_in,
                       const hit_record &rec,
                       color &attenuation,
                       ray &scattered) const override
  {
    attenuation = color(1, 1, 1);
    double refraction_ratio = rec.front_face ? 1.0 / index_of_refraction : index_of_refraction;
    vec3 ray_in_unit_direction = unit_vector(ray_in.direction);
    double cos_theta = fmin(ray_in_unit_direction.dot(rec.normal), 1.0);
    double sin_theta = sqrt(1 - (cos_theta * cos_theta));
    auto scattered_direction = refract(ray_in_unit_direction, rec.normal, refraction_ratio);
    bool cannot_refract = sin_theta * refraction_ratio > 1.0;
    /* rays reflect not only when it passes critical angle but also in other situations as
     * specified by schilk's approximation */
    if (cannot_refract || reflectance(cos_theta, refraction_ratio)) {
      /* Total internal Reflection */
      scattered_direction = reflect(ray_in_unit_direction, rec.normal);
    }
    scattered = ray(rec.p, scattered_direction);
    return true;
  }

 private:
  static double reflectance(double cosine, double ref_idx)
  {
    /* Use Schlick's approximation for reflectance. */
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
  }
};

#endif

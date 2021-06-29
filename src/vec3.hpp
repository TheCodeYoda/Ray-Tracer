#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "constants.hpp"

using std::sqrt;

class vec3 {
 public:
  double x;
  double y;
  double z;

 public:
  /* ctors */
  vec3()
  {
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
  }
  vec3(double x, double y, double z)
  {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  /* operator functions -,+=,*=,/= */
  vec3 operator-() const
  {
    return vec3(-this->x, -this->y, -this->z);
  }

  vec3 &operator+=(const vec3 &rhs)
  {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return (*this);
  }

  /* lhs vec rhs constant */
  vec3 &operator*=(const double rhs)
  {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return (*this);
  }

  /* lhs vec rhs constant */
  vec3 &operator/=(const double rhs)
  {
    return *this *= (1 / rhs);
  }

  /* length functions */
  double length_square() const
  {
    return (this->x * this->x) + (this->y) * (this->y) + (this->z * this->z);
  }

  double length() const
  {
    return sqrt(this->length_square());
  }

  double dot(const vec3 &rhs) const
  {
    return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z;
  }

  vec3 cross(const vec3 &rhs)
  {
    return vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
  }

  bool near_zero() const
  {
    /* Return true if the vector is close to zero in all dimensions. */
    const auto s = 1e-8;
    return (fabs(this->x) < s) && (fabs(this->y) < s) && (fabs(this->z) < s);
  }

  /* random vector gen functions */
  static vec3 random()
  {
    return vec3(random_double(), random_double(), random_double());
  }

  static vec3 random(double min, double max)
  {
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
  }
};

/* friend operator functions and vec3 interface */

vec3 operator+(const vec3 &lhs, const vec3 &rhs)
{
  return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

vec3 operator-(const vec3 &lhs, const vec3 &rhs)
{
  return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

vec3 operator*(const vec3 &lhs, const vec3 &rhs)
{
  return vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

vec3 operator*(const double lhs, const vec3 &rhs)
{
  return vec3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

vec3 operator*(const vec3 &lhs, const double rhs)
{
  return vec3(rhs * lhs.x, rhs * lhs.y, rhs * lhs.z);
}

vec3 operator/(const vec3 &lhs, const double rhs)
{
  return lhs * (1 / rhs);
}

vec3 unit_vector(const vec3 &v)
{
  return v / v.length();
}

/* gives a random point inside unit sphere */

vec3 random_in_unit_sphere()
{
  while (1) {
    auto point = vec3::random(-1, 1);
    if (point.length_square() >= 1)
      continue;
    return point;
  }
}

vec3 random_in_hemisphere(const vec3 &normal)
{
  vec3 in_unit_sphere = random_in_unit_sphere();
  if (in_unit_sphere.dot(normal) > 0.0) /* In the same hemisphere as the normal */
    return in_unit_sphere;
  else
    return -in_unit_sphere;
}

vec3 random_unit_vector()
{
  return unit_vector(random_in_unit_sphere());
}

vec3 random_in_unit_disk()
{
  while (true) {
    auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
    if (p.length_square() >= 1)
      continue;
    return p;
  }
}

/* standard reflection in vector form it returns direction of reflected ray */
vec3 reflect(const vec3 &v, const vec3 &normal)
{
  return v - 2 * v.dot(normal) * normal;
}

/* standard refraction in vector form it returns direction of refracted ray */
vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat)
{
  auto cos_theta = fmin((-uv).dot(n), 1.0);
  vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
  vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_square())) * n;
  return r_out_perp + r_out_parallel;
}

/* aliasing */
using point3 = vec3;
using color = vec3;

#endif

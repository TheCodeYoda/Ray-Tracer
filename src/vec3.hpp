#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

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
  vec3 &operator-()
  {
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;
    return (*this);
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
  double length_square()
  {
    return (this->x * this->x) + (this->y) * (this->y) + (this->z * this->z);
  }

  double length()
  {
    return sqrt(this->length_square());
  }

  double dot(const vec3 &rhs)
  {
    return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z;
  }

  vec3 cross(const vec3 &rhs)
  {
    return vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
  }

  vec3 unit_vector()
  {
    double mag = this->length();
    return vec3(this->x / mag, this->y / mag, this->z / mag);
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

/* aliasing */
using point3 = vec3;
using color = vec3;

#endif

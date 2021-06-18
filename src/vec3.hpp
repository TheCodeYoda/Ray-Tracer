#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class Vec3 {
 public:
  double x;
  double y;
  double z;

 public:
  /* ctors */
  Vec3()
  {
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
  }
  Vec3(double x, double y, double z)
  {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  /* operator functions -,+=,*=,/= */
  Vec3 &operator-()
  {
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;
    return (*this);
  }

  Vec3 &operator+=(const Vec3 &rhs)
  {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return (*this);
  }

  /* lhs vec rhs constant */
  Vec3 &operator*=(const double rhs)
  {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return (*this);
  }

  /* lhs vec rhs constant */
  Vec3 &operator/=(const double rhs)
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

  double dot(const Vec3 &rhs)
  {
    return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z;
  }

  Vec3 cross(const Vec3 &rhs)
  {
    return Vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
  }

  Vec3 unit_vector()
  {
    double mag = this->length();
    return Vec3(this->x / mag, this->y / mag, this->z / mag);
  }
};

/* friend operator functions and Vec3 interface */

Vec3 operator+(const Vec3 &lhs, const Vec3 &rhs)
{
  return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vec3 operator-(const Vec3 &lhs, const Vec3 &rhs)
{
  return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vec3 operator*(const Vec3 &lhs, const Vec3 &rhs)
{
  return Vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

Vec3 operator*(const double lhs, const Vec3 &rhs)
{
  return Vec3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

Vec3 operator*(const Vec3 &lhs, const double rhs)
{
  return Vec3(rhs * lhs.x, rhs * lhs.y, rhs * lhs.z);
}

Vec3 operator/(const Vec3 &lhs, const double rhs)
{
  return lhs * (1 / rhs);
}

/* aliasing */
using point3 = Vec3;
using color = Vec3;

#endif

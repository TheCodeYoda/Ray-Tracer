#include "color.hpp"
#include "vec3.hpp"
#include "ray.hpp"

#include <iostream>

/* Sphere equation centered at point P(x,y,z) : (P-C)(P-C) = r^2 */
/*   P --> (x,y,z) */
/*   C --> (Cx,Cy,Cz) */
/* P(t) = origin + direction*t */
/* substitute P(t) in sphere equation and find discriminant to find roots of eqn wich tells about
 * intersection */

/* utility function to check imtersection of ray with sphere */
bool hit_sphere(const point3 &center, double radius, const ray &r)
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
  return (discriminant > 0);
}

/* after intersection if the ray hits sphere it returns color of sphere otherwise it returns
 * background color */
color ray_color(const ray &r)
{
  /* if intersects return red */
  if (hit_sphere({0, 0, -1}, 0.5, r)) {
    return color(1, 0, 0);
  }
  /* no intersection return black */
  return color(0, 0, 0);
}

/* generates ppm file */
int main()
{

  // Image
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);

  // Camera

  auto viewport_height = 2.0;
  auto viewport_width = aspect_ratio * viewport_height;
  auto focal_length = 1.0;

  auto origin = point3(0, 0, 0);
  auto horizontal = vec3(viewport_width, 0, 0);
  auto vertical = vec3(0, viewport_height, 0);
  auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

  // Render

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      auto u = double(i) / (image_width - 1);
      auto v = double(j) / (image_height - 1);
      ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
      color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }

  std::cerr << "\nDone.\n";
}

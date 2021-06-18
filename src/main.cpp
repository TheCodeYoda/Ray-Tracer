#include "color.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "sphere.hpp"

#include <iostream>

/* Sphere equation centered at point P(x,y,z) : (P-C)(P-C) = r^2 */
/*   P --> (x,y,z) */
/*   C --> (Cx,Cy,Cz) */
/* P(t) = origin + direction*t */
/* substitute P(t) in sphere equation and find discriminant to find roots of eqn wich tells about
   intersection */

/* after intersection if the ray hits sphere it returns color of sphere otherwise it returns
 * background color */
color ray_color(const ray &r)
{
  /* if intersects return red */
  auto sp = sphere({0, 0, -1}, 0.5);
  auto time = sp.hit(r);
  if (time > -1.0) {
    /* r.at(t) ---> point of intersection */
    /* normal ----> surface normal vector */
    auto normal = r.at(time) - sp.center;
    /* shading */
    return 0.5 * color(normal.x + 1, normal.y + 1, normal.z + 1);
  }
  /* no intersection return blue-white gradient background */
  vec3 unit_direction = unit_vector(r.direction);
  auto t = 0.5 * (unit_direction.y + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

/* generates ppm file */
int main()
{

  /* Image */
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);

  /* Camera */

  auto viewport_height = 2.0;
  auto viewport_width = aspect_ratio * viewport_height;
  auto focal_length = 1.0;

  auto origin = point3(0, 0, 0);
  auto horizontal = vec3(viewport_width, 0, 0);
  auto vertical = vec3(0, viewport_height, 0);
  auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

  /* Render */

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

#include "color.hpp"
#include "sphere.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "constants.hpp"
#include "camera.hpp"

#include <iostream>

/* Sphere equation centered at point P(x,y,z) : (P-C)(P-C) = r^2 */
/*   P --> (x,y,z) */
/*   C --> (Cx,Cy,Cz) */
/* P(t) = origin + direction*t */
/* substitute P(t) in sphere equation and find discriminant to find roots of eqn wich tells about
   intersection */

/* after intersection if the ray hits sphere it returns color of sphere otherwise it returns
 * background color */
color ray_color(const ray &r, hittable_list &scene)
{
  /* if intersects return red */
  hit_record rec;
  if (scene.hit(r, 0, infinity, rec)) {
    /* rec stores all hit info such as normal and stuff */
    /* shading */
    return 0.5 * (rec.normal + color(1, 1, 1));
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
  const int samples_per_pixel = 100;
  /* Scene */

  hittable_list scene;
  scene.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  scene.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

  /* Camera */
  camera cam;

  /* Render */

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      color pixel_color(0, 0, 0);
      /* antialiasing adding more pixels to prevent jaggedness */
      for (int sample = 0; sample < samples_per_pixel; ++sample) {
        auto u = double(i) / (image_width - 1);
        auto v = double(j) / (image_height - 1);
        ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, scene);
      }
      write_color(std::cout, pixel_color, samples_per_pixel);
    }
  }

  std::cerr << "\nDone.\n";
}

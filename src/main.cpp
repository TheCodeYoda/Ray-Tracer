#include "color.hpp"
#include "sphere.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "constants.hpp"
#include "camera.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "material.hpp"

#include <iostream>

/* Sphere equation centered at point P(x,y,z) : (P-C)(P-C) = r^2 */
/*   P --> (x,y,z) */
/*   C --> (Cx,Cy,Cz) */
/* P(t) = origin + direction*t */
/* substitute P(t) in sphere equation and find discriminant to find roots of eqn wich tells about
   intersection */

/* after intersection if the ray hits sphere it returns color of sphere otherwise it returns
 * background color */

/* make it recursive and set depth also to avoid stack smashing */
color ray_color(const ray &r, hittable_list &scene, int depth) /* */
{
  hit_record rec;
  /* max depth reached no light */
  if (depth <= 0) {
    return color(0, 0, 0);
  }

  if (scene.hit(r, 0.001, infinity, rec)) {
    /* rec stores all hit info such as normal and stuff */
    ray scattered;
    color attenuation;
    if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
      return attenuation * ray_color(scattered, scene, depth - 1);
    }
    return color(0, 0, 0);
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
  int max_depth = 10; /* recursion depth after reflections(random) for diffuse materials*/
  /* Scene */

  hittable_list scene;
  auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
  auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
  auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

  scene.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
  scene.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
  scene.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
  scene.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

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
        auto u = (i + random_double()) / (image_width - 1);
        auto v = (j + random_double()) / (image_height - 1);
        ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, scene, max_depth);
      }
      write_color(std::cout, pixel_color, samples_per_pixel);
    }
  }
  std::cerr << "\nDone.\n";
}

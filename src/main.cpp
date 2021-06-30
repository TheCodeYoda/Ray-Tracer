#include "color.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
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

/* generate random scene */

hittable_list random_scene()
{
  /* hittable_list scene; */
  /* auto mat = make_shared<lambertian>(color(0.4, 0.2, 0.1)); */
  /* scene.add(make_shared<triangle>(point3(-2, 1, 0), point3(3, 2, 0), point3(1, 5, 0), mat)); */
  /* return scene; */

  hittable_list scene;

  auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
  scene.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

  for (int a = -3; a < 3; a++) {
    for (int b = -2; b < 2; b++) {
      auto choose_mat = random_double();
      point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

      if ((center - point3(4, 0.2, 0)).length() > 0.9) {
        shared_ptr<material> sphere_material;

        if (choose_mat < 0.8) {
          /* diffuse */
          auto albedo = color::random() * color::random();
          sphere_material = make_shared<lambertian>(albedo);
          scene.add(make_shared<sphere>(center, 0.2, sphere_material));
        }
        else if (choose_mat < 0.95) {
          /* metal */
          auto albedo = color::random(0.5, 1);
          auto fuzz = random_double(0, 0.5);
          sphere_material = make_shared<metal>(albedo, fuzz);
          scene.add(make_shared<sphere>(center, 0.2, sphere_material));
        }
        else {
          /* glass */
          sphere_material = make_shared<dielectric>(1.5);
          scene.add(make_shared<sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = make_shared<dielectric>(1.5);
  scene.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

  auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
  scene.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

  auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
  scene.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

  return scene;
}

/* generates ppm file */
int main()
{

  /* Image */

  const auto aspect_ratio = 3.0 / 2.0;
  const int image_width = 1200;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 500;
  const int max_depth = 10;

  /* World */

  hittable_list scene = random_scene();

  /* Camera */

  point3 lookfrom(13, 2, 3);
  point3 lookat(0, 0, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  auto aperture = 0.1;

  camera cam(lookfrom, lookat, vup, 180, aspect_ratio, aperture, dist_to_focus);

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

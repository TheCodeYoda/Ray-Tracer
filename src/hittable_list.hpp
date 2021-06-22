#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.hpp"

#include <vector>
#include <memory>

using std::make_shared;
using std::shared_ptr;
using std::vector;

class hittable_list : public hittable {
 public:
  vector<shared_ptr<hittable>> objects;

 public:
  /* ctors */
  hittable_list(){};

  hittable_list(shared_ptr<hittable> &object)
  {
    this->add(object);
  }
  /* functions add and clear */
  void add(shared_ptr<hittable> object)
  {
    this->objects.push_back(object);
  }

  void clear()
  {
    this->objects.clear();
  }

  virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec);
};

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec)
{
  auto closest = t_max;
  auto flag = false;
  hit_record temp_rec;

  /* going through all the objects and checking hit point and storing hit info in rec */
  /* object is a shared_ptr (smart pointer) */
  for (const auto &object : this->objects) {
    if (object->hit(r, t_min, closest, temp_rec)) {
      flag = true;
      closest = temp_rec.t;
      rec = temp_rec;
    }
  }
  return flag;
}

#endif

#ifndef SPHERE_H
#define SPHERE_H

#include "./shape.h"
#include <cmath>
#include <vector>

#define DEBUG_SPHERE 0

class sphere : public shape {
public:
  // sphere() : shape() { xsSecond.resize(2, intersection(this)); }
  sphere() { xsSecond.resize(2, intersection(this)); }
  sphere(point ori, float r);
  ~sphere() {}
  static sphere glassSphere();
  void print();
  std::vector<intersection> local_intersect(ray &r);
  vec localNormalAt(point &objPoint);

private:
  float radius = 1;
  point origin = point(0, 0, 0);
  std::vector<intersection> xsSecond;
};

#endif

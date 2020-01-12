#include "./point.h"
#include "./vec.h"
#include "mat.h"
#include "tuple.h"

#ifndef RAY_H
#define RAY_H

class ray {
public:
  ray(point ori, vec dir) {
    origin = ori;
    direction = dir;
  }

  ray(const ray &r) {
    origin = r.origin;
    direction = r.direction;
  }

  point position(float t) { return origin + (direction * t); }

  point origin;
  vec direction;

private:
};

namespace {
// perform transform on ray
ray operator*(mat m, ray r) { return ray(m * r.origin, m * r.direction); }
} // namespace

#endif

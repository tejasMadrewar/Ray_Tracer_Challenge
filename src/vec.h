#include "tuple.h"

#ifndef VEC_H
#define VEC_H

class vec : public tuple {
public:
  vec() : tuple(0, 0, 0, 0) {}
  vec(float x, float y, float z) : tuple(x, y, z, 0) {}
  vec(const vec &v) {
    t[0] = v.t[0];
    t[1] = v.t[1];
    t[2] = v.t[2];
    t[3] = v.t[3];
  }
  vec(const tuple tup) {
    t[0] = tup.t[0];
    t[1] = tup.t[1];
    t[2] = tup.t[2];
    t[3] = tup.t[3];
  }

  ~vec() {}

  void setW(float a) {}

  // vector subtraction
  vec operator-(vec a) {
    return vec(t[0] - a.t[0], t[1] - a.t[1], t[2] - a.t[2]);
  }

  // vector addition
  vec operator+(vec a) {
    return vec(t[0] + a.t[0], t[1] + a.t[1], t[2] + a.t[2]);
  }

  // negating operator
  vec operator-() { return vec(-t[0], -t[1], -t[2]); }

  // magnitude
  auto mag() -> float {
    return sqrt((t[0] * t[0]) + (t[1] * t[1]) + (t[2] * t[2]));
  }
  // normalize
  auto norm() -> vec {
    auto magnitude = sqrt((t[0] * t[0]) + (t[1] * t[1]) + (t[2] * t[2]));
    return vec(t[0] / magnitude, t[1] / magnitude, t[2] / magnitude);
  }

  // cross
  friend auto cross(const tuple &a, const tuple &b) -> vec {
    return vec(a.t[1] * b.t[2] - a.t[2] * b.t[1],
               a.t[2] * b.t[0] - a.t[0] * b.t[2],
               a.t[0] * b.t[1] - a.t[1] * b.t[0]

    );
  }

private:
};

#endif

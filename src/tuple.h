#ifndef TUPLE_H
#define TUPLE_H

#include <iostream>
#include <math.h>

class tuple {
  // ordered elements
  // x y z w
  // if w = 0 tuple is point
  // if w = 1 tuple is vector
public:
  float t[4]{};
  // contructor
  tuple() {
    t[0] = 0;
    t[1] = 0;
    t[2] = 0;
    t[3] = 0;
  }

  tuple(float x, float y, float z, float w) {
    t[0] = x;
    t[1] = y;
    t[2] = z;
    t[3] = w;
  }

  tuple(const tuple &tup) {
    t[0] = tup.t[0];
    t[1] = tup.t[1];
    t[2] = tup.t[2];
    t[3] = tup.t[3];
  }
  ~tuple() = default;

  // get value
  auto getX() -> float { return t[0]; }
  auto getY() -> float { return t[1]; }
  auto getZ() -> float { return t[2]; }
  auto getW() -> float { return t[3]; }

  // set value
  void setX(float a) { t[0] = a; }
  void setY(float a) { t[1] = a; }
  void setZ(float a) { t[2] = a; }
  void setW(float a) { t[3] = a; }

  // point or vector check
  auto isPoint() -> bool { return (t[3] == 1); }
  auto isVector() -> bool { return (t[3] == 0); }

  // compare
  auto operator==(const tuple &a) -> bool {
    float EPSILON = 0.0001;
    return (fabs(t[0] - a.t[0]) < EPSILON) && (fabs(t[1] - a.t[1]) < EPSILON) &&
           (fabs(t[2] - a.t[2]) < EPSILON) && (fabs(t[3] - a.t[3]) < EPSILON);
  }

  // addition
  auto operator+(const tuple &a) -> tuple {
    return tuple(t[0] + a.t[0], t[1] + a.t[1], t[2] + a.t[2], t[3] + a.t[3]);
  }

  // subtraction
  auto operator-(const tuple &a) -> tuple {
    return tuple(t[0] - a.t[0], t[1] - a.t[1], t[2] - a.t[2], t[3] - a.t[3]);
  }

  // negating operator
  auto operator-() -> tuple { return tuple(-t[0], -t[1], -t[2], -t[3]); }

  // scalar division
  auto operator/(float a) -> tuple {
    return tuple(t[0] / a, t[1] / a, t[2] / a, t[3] / a);
  }
  // scalar multiplication
  friend auto operator*(const tuple &a, float b) -> tuple {
    return tuple(a.t[0] * b, a.t[1] * b, a.t[2] * b, a.t[3] * b);
  }
  friend auto operator*(float b, const tuple &a) -> tuple {
    return tuple(a.t[0] * b, a.t[1] * b, a.t[2] * b, a.t[3] * b);
  }

  // dot product
  friend auto dot(const tuple &a, const tuple &b) -> float {
    return (a.t[0] * b.t[0] + a.t[1] * b.t[1] + a.t[2] * b.t[2] +
            a.t[3] * b.t[3]);
  }

  // magnitude
  auto mag() -> float {
    return sqrt((t[0] * t[0]) + (t[1] * t[1]) + (t[2] * t[2]) + (t[3] * t[3]));
  }

  // output tuple
  void print() {
    std::cout << t[0] << " " << t[1] << " " << t[2] << " " << t[3];
  }

private:
};

#endif

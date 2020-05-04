#include "tuple.h"

#ifndef COLOR_H
#define COLOR_H

class color : public tuple {
public:
  color() {
    t[0] = 0;
    t[1] = 0;
    t[2] = 0;
    t[3] = 0;
  }
  color(float r, float g, float b) {
    t[0] = r;
    t[1] = g;
    t[2] = b;
    t[3] = 0;
  }
  color(tuple &tup) {
    t[0] = tup.t[0];
    t[1] = tup.t[1];
    t[2] = tup.t[2];
    t[3] = 0;
  }

  float red() const { return t[0]; }
  float green() const { return t[1]; }
  float blue() const { return t[2]; }

  color operator+(const color &a) {
    return color(t[0] + a.t[0], t[1] + a.t[1], t[2] + a.t[2]);
  }

  color operator-(const color &a) {
    return color(t[0] - a.t[0], t[1] - a.t[1], t[2] - a.t[2]);
  }

  friend color operator*(const color &a, const float &b) {
    return color(a.t[0] * b, a.t[1] * b, a.t[2] * b);
  }

  friend color operator*(const float &b, const color &a) {
    return color(a.t[0] * b, a.t[1] * b, a.t[2] * b);
  }

  friend color operator*(const color &a, const color &b) {
    return color(a.t[0] * b.t[0], a.t[1] * b.t[1], a.t[2] * b.t[2]);
  }
};

#endif

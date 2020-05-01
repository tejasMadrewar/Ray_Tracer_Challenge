#ifndef PATTERN_H
#define PATTERN_H

#include "color.h"
#include "mat.h"
#include "point.h"
//#include "shape.h"
#include <memory>

// ------------------------------------------------------------------
// declaration of pattern
// ------------------------------------------------------------------
class pattern {
public:
  pattern() {
    a = white;
    b = black;
  }
  virtual ~pattern() {}
  void setTransform(mat &m) {
    transformMat = m;
    inverseTransformMat = transformMat.inverse();
  }
  void setColor(color &c1, color &c2) {
    a = c1;
    b = c2;
  }
  virtual color stripeAt(point &p) = 0;
  // color stripeAtObject(shape &s, point &worldPoint);
  color stripeAtObject(mat &inverseTransformMatofShape, point &worldPoint) {
    color result;
    point objectPoint;
    point patternPoint;
    // objectPoint = s.getInverseTransform() * worldPoint;
    objectPoint = inverseTransformMatofShape * worldPoint;
    patternPoint = this->inverseTransformMat * objectPoint;

    return this->stripeAt(objectPoint);
  }
  color black = color(0, 0, 0), white = color(1, 1, 1);
  color a, b;

protected:
  mat transformMat = mat(4);
  mat inverseTransformMat = mat(4);
};

// test pattern class
// ------------------------------------------------------------------
class test_pattern : public pattern {
  color stripeAt(point &p) override { return color(1.0, 2.0, 3.0); }
};
// ------------------------------------------------------------------

#endif

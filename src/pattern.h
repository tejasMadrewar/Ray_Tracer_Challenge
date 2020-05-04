#ifndef PATTERN_H
#define PATTERN_H

#include "color.h"
#include "mat.h"
#include "point.h"
#include <memory>

class pattern {
public:
  pattern();
  virtual ~pattern() {}
  virtual color stripeAt(point &p) = 0;
  void setTransform(mat &m);
  void setColor(color &c1, color &c2);
  mat &Transform() { return transformMat; }
  mat &InverseTransform() { return inverseTransformMat; }
  color stripeAtObject(mat &inverseTransformMatofShape, point &worldPoint);
  color black = color(0, 0, 0), white = color(1, 1, 1);
  color a, b;

private:
  mat transformMat = mat::Identity(4);
  mat inverseTransformMat = mat::Identity(4);
};

class test_pattern : public pattern {
  color stripeAt(point &p) override { return color(1.0, 2.0, 3.0); }
};

class stripePattern : public pattern {
public:
  stripePattern(color m, color n);
  color stripeAt(point &p);
};

class gradientPattern : public pattern {
public:
  gradientPattern(color m, color n);
  color stripeAt(point &p);
};

class ringPattern : public pattern {
public:
  ringPattern(color m, color n);
  color stripeAt(point &p);
};

class threeDCheckerPattern : public pattern {
public:
  threeDCheckerPattern(color m, color n);
  color stripeAt(point &p);
};

#endif

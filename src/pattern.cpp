#include "./pattern.h"

pattern::pattern() {
  a = white;
  b = black;
}

void pattern::setTransform(mat &m) {
  transformMat = m;
  inverseTransformMat = transformMat.inverse();
}

void pattern::setColor(color &c1, color &c2) {
  a = c1;
  b = c2;
}

color pattern::stripeAtObject(mat &inverseTransformMatofShape,
                              point &worldPoint) {
  color result;
  point objectPoint;
  point patternPoint;
  objectPoint = inverseTransformMatofShape * worldPoint;
  patternPoint = this->inverseTransformMat * objectPoint;
  return this->stripeAt(objectPoint);
}

stripePattern::stripePattern(color m, color n) {
  a = m;
  b = n;
}

color stripePattern::stripeAt(point &p) {
  return ((int)floor(p.getX()) % 2 == 0) ? a : b;
}

gradientPattern::gradientPattern(color m, color n) {
  a = m;
  b = n;
}

color gradientPattern::stripeAt(point &p) {
  float fraction = p.getX() - floor(p.getX());
  color distance, result;
  distance = b - a;
  result = (a + (distance * fraction));
  return result;
}

ringPattern::ringPattern(color m, color n) {
  a = m;
  b = n;
}

color ringPattern::stripeAt(point &p) {
  float m = sqrt((p.getX() * p.getX()) + (p.getZ() * p.getZ()));
  int n = int(floor(m)) % 2;
  return (n == 0) ? a : b;
}

threeDCheckerPattern::threeDCheckerPattern(color m, color n) {
  a = m;
  b = n;
}

color threeDCheckerPattern::stripeAt(point &p) {
  float m = fabs(p.getZ()) + fabs(p.getY()) + fabs(p.getX());
  int n = int(m) % 2;
  return (n == 0.0) ? a : b;
}

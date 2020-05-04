#include "./shape.h"

void shape::setTransform(mat m) {
  Transform = m;
  TransformInverse = m.inverse();
  TransformInverseTranspose = TransformInverse.transpose();
}

std::vector<intersection> shape::intersect(ray &r) {
  ray local_ray(point(0, 0, 0), vec(0, 0, 0));
  local_ray = TransformInverse * r;
  return local_intersect(local_ray);
}

vec shape::normalAt(point &p) {
  point local_point = TransformInverse * p;
  vec local_normal = localNormalAt(local_point);
  vec world_normal = TransformInverseTranspose * local_normal;
  world_normal.setW(0);

  return world_normal.norm();
}

color shape::ColorAtShape(point &worldPoint) {
  color result;
  point objectPoint;
  point patternPoint;
  objectPoint = this->TransformInverse * worldPoint;
  patternPoint = patternPtr->InverseTransform() * objectPoint;
  result = patternPtr->stripeAt(patternPoint);

  return result;
}

void shape::setStripePattern(color c1, color c2) {
  patternPtr = std::shared_ptr<pattern>(new stripePattern(c1, c2));
}

void shape::setStripePattern(color c1, color c2, mat &m) {
  patternPtr = std::shared_ptr<pattern>(new stripePattern(c1, c2));
  patternPtr->setTransform(m);
}

void shape::setGradientPattern(color c1, color c2) {
  patternPtr = std::shared_ptr<pattern>(new gradientPattern(c1, c2));
}

void shape::setGradientPattern(color c1, color c2, mat &m) {
  patternPtr = std::shared_ptr<pattern>(new gradientPattern(c1, c2));
  patternPtr->setTransform(m);
}

void shape::setRingPattern(color c1, color c2) {
  patternPtr = std::shared_ptr<pattern>(new ringPattern(c1, c2));
}

void shape::setRingPattern(color c1, color c2, mat &m) {
  patternPtr = std::shared_ptr<pattern>(new ringPattern(c1, c2));
  patternPtr->setTransform(m);
}

void shape::setThreeDCheckerPattern(color c1, color c2) {
  patternPtr = std::shared_ptr<pattern>(new threeDCheckerPattern(c1, c2));
}

void shape::setThreeDCheckerPattern(color c1, color c2, mat &m) {
  patternPtr = std::shared_ptr<pattern>(new threeDCheckerPattern(c1, c2));
  patternPtr->setTransform(m);
}

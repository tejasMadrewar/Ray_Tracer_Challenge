#include "./plane.h"

plane::plane() {
  xsSingle.resize(1, intersection(this));
  NormalVec = vec(0, 1, 0); // constant for all points on plane
}

std::vector<intersection> plane::local_intersect(ray &r) {

  const float EPSILON = 0.0001;
  if (fabs(r.direction.getY()) < EPSILON) {
    return xs;
  }

  float t = -r.origin.getY() / r.direction.getY();
  xsSingle[0].intersected = t;
  return xsSingle;
}

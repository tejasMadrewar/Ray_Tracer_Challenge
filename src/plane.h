#ifndef PLANE_H
#define PLANE_H

#include "./shape.h"
#include "intersection.h"

// plane by default is along x and z axis and is passing through origin
class plane : public shape {
public:
  plane();
  std::vector<intersection> local_intersect(ray &r);
  vec localNormalAt(point &p) { return NormalVec; }

private:
  std::vector<intersection> xs;
  std::vector<intersection> xsSingle;
  vec NormalVec;
};

#endif

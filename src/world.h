#ifndef WORLD_H
#define WORLD_H

#include <vector>
#define WORLD_DEBUG 0

#include "light.h"
#include "mat.h"
#include "material.h"
#include "plane.h"
#include "sphere.h"
#include "transform.h"
#include <algorithm>
#include <memory>

class world {
public:
  world() {}
  ~world() {}
  std::vector<intersection> intersect_world(ray &r);
  color shadeHit(preComputed p, int remaining = 4);
  color colorAt(ray r, int remaining = 4);
  color reflectedColorAt(preComputed p, int n = 1);
  color refractedColorAt(preComputed p, int n = 1);
  void add_sphere(const mat &trans, const material &m);
  void add_plane(const mat &trans, const material &m);
  void add_sphere(const mat &trans);
  void add_shape(std::shared_ptr<shape> sptr);
  bool isShadowed(point &p);

  static world default_world();

public:
  pointLight worldLight;
  // std::vector<shape *> sVec;
  std::vector<std::shared_ptr<shape>> vecShapes;

private:
  material m;
  transform t;
};

#endif

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#define WORLD_DEBUG 0

#include "./light.h"
#include "./material.h"
#include "./plane.h"
#include "./sphere.h"
#include "./transform.h"
#include "mat.h"
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
  void add_sphere(const mat &trans, const material &m);
  void add_plane(const mat &trans, const material &m);
  void add_sphere(const mat &trans);
  void add_shape(std::shared_ptr<shape> sptr);
  bool isShadowed(point &p);

  static world default_world() {
    world w;
    material m;
    transform t;

    w.worldLight.intensity = color(1, 1, 1);
    w.worldLight.position = point(-10, 10, -10);

    m.col = color(0.8, 1.0, 0.6);
    m.diffuse = 0.7;
    m.specular = 0.2;

    w.add_sphere(mat::Identity(4), m);
    w.add_sphere(t.scale(0.5, 0.5, 0.5));

    return w;
  }

public:
  pointLight worldLight;
  // std::vector<shape *> sVec;
  std::vector<std::shared_ptr<shape>> vecShapes;

private:
  material m;
  transform t;
};

#endif

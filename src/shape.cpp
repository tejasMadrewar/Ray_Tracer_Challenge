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

#ifndef CAMERA_H
#define CAMERA_H

#include "./canvas.h"
#include "./mat.h"
#include "./ray.h"
#include "./transformation.h"
#include "./world.h"
#include <cmath>

class camera {
public:
  camera(int thsize, int tvsize, float tfieldOfView);
  ray ray_for_pixel(int px, int py);
  void setTransform(mat &trans);
  mat getTransform() { return transform; }
  canvas render(world &w);

  float hsize, vsize;
  float fieldOfView;
  float pixelSize;
  float halfView, aspect, halfWidth, halfHeight;

private:
  mat transform = mat::Identity(4);
  mat transformInverse = mat::Identity(4);
};

#endif

#ifndef LIGHT_H
#define LIGHT_H

#include "./color.h"
#include "./point.h"

class pointLight {
public:
  pointLight() {
    intensity = color(0, 0, 0);
    position = point(0, 0, 0);
  }
  color intensity;
  point position;
};

#endif

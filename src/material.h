#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include <memory>

#define MATERIAL_DEBUG 0

class material {

public:
  material() {}

  material(const material &n) {
    ambient = n.ambient;
    diffuse = n.diffuse;
    specular = n.specular;
    shiniess = n.shiniess;
    reflective = n.reflective;
    transparency = n.transparency;
    refractiveIndex = n.refractiveIndex;
    col = n.col;
  }

  bool operator==(const material &n) {
    return (ambient == n.ambient && diffuse == n.diffuse &&
            specular == n.specular && shiniess == n.shiniess &&
            reflective == n.reflective && col == n.col);
  }

  // color
  color col = color(1, 1, 1);
  // 0-1 value
  float ambient = 0.1;
  float diffuse = 0.9;
  float specular = 0.9;
  float reflective = 0.0;
  // refraction and transparency
  float transparency = 0.0;
  float refractiveIndex = 1.0;

  // 10 very large highlight and d200 very small highlight
  float shiniess = 200;
};

#endif

#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "stripePattern.h"
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
    col = n.col;
    patternPtr = n.patternPtr;
  }

  bool operator==(const material &n) {
    return (ambient == n.ambient && diffuse == n.diffuse &&
            specular == n.specular && shiniess == n.shiniess);
  }

  // color
  color col = color(1, 1, 1);
  // 0-1 value
  float ambient = 0.1;
  float diffuse = 0.9;
  float specular = 0.9;

  // 10 very large highlight and d200 very small highlight
  float shiniess = 200;

  // pattern
  void setStripePattern(color c1, color c2) {
    patternPtr = std::shared_ptr<pattern>(new stripePattern(c1, c2));
  }
  void setPattern(std::shared_ptr<pattern> p) { patternPtr = p; }
  std::shared_ptr<pattern> patternPtr = nullptr;
};

#endif

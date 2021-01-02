#ifndef TRANSFORM
#define TRANSFORM

#include "./mat.h"
#include <cmath>
#include <math.h>

const float PI = 3.1415927;

class transform {
public:
  transform() {}
  ~transform() {}
  static mat translate(float x, float y, float z);
  static mat scale(float x, float y, float z);
  static mat rotX(const float radian);
  static mat rotY(const float radian);
  static mat rotZ(const float radian);
  static mat shear(const float xy, const float xz, const float yx,
                   const float yz, const float zx, const float zy);

private:
};

#endif

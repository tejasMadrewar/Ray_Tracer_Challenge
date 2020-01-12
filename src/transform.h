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

  static mat translate(float x, float y, float z) {
    mat result(4);
    result = result.Identity(4);
    result.at(0, 3) = x;
    result.at(1, 3) = y;
    result.at(2, 3) = z;

    return result;
  }

  static mat scale(float x, float y, float z) {
    mat result(4);
    result = result.Identity(4);
    result.at(0, 0) = x;
    result.at(1, 1) = y;
    result.at(2, 2) = z;

    return result;
  }

  static mat rotX(const float radian) {
    mat result(4);
    result = result.Identity(4);
    result.at(0, 0) = 1;
    result.at(1, 1) = cos(radian);
    result.at(1, 2) = -sin(radian);
    result.at(2, 1) = sin(radian);
    result.at(2, 2) = cos(radian);
    result.at(3, 3) = 1;

    return result;
  }

  static mat rotY(const float radian) {
    mat result(4);
    result = result.Identity(4);
    result.at(0, 0) = cos(radian);
    result.at(0, 2) = sin(radian);
    result.at(1, 1) = 1;
    result.at(2, 0) = -sin(radian);
    result.at(2, 2) = cos(radian);
    result.at(3, 3) = 1;

    return result;
  }

  static mat rotZ(const float radian) {
    mat result(4);
    result = result.Identity(4);
    result.at(0, 0) = cos(radian);
    result.at(0, 1) = -sin(radian);
    result.at(1, 0) = sin(radian);
    result.at(1, 1) = cos(radian);
    result.at(2, 2) = 1;
    result.at(3, 3) = 1;

    return result;
  }

  static mat shear(const float xy, const float xz, const float yx,
                   const float yz, const float zx, const float zy) {
    mat result(4);
    result = result.Identity(4);
    result.at(0, 1) = xy;
    result.at(0, 2) = xz;
    result.at(1, 0) = yx;
    result.at(1, 2) = yz;
    result.at(2, 0) = zx;
    result.at(2, 1) = zy;

    return result;
  }

private:
};

#endif

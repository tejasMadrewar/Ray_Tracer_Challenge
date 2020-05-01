#ifndef SHAPE_H
#define SHAPE_H

#include "./intersection.h"
#include "./mat.h"
#include "./material.h"
#include "./point.h"
#include "./ray.h"
#include "./vec.h"

#include <vector>

class shape {
public:
  shape() {}
  virtual ~shape() {}
  // material
  void setMaterial(material n) { m = n; }
  material getMaterial() { return m; }
  // transform
  void setTransform(mat m);
  mat getTransform() const { return Transform; }
  mat &getInverseTransform() { return TransformInverse; }

  // intersection with ray
  std::vector<intersection> intersect(ray &r);
  // normal to shape
  vec normalAt(point &p);

  // virual methods
  // implented in inherated class
  virtual std::vector<intersection> local_intersect(ray &r) = 0;
  virtual vec localNormalAt(point &p) = 0;

  material m;
  ray saved_ray;

protected:
  mat Transform = mat::Identity(4);
  mat TransformInverse = mat::Identity(4);
  mat TransformInverseTranspose = mat::Identity(4);
};

// from intersection.h
namespace {

preComputed prepareComputation(intersection i, ray r) {
  float EPSILON = 0.001;
  preComputed result;
  result.objptr = i.obj;
  result.eyev = -r.direction;
  result.position = r.position(i.intersected);
  result.normalv = i.obj->normalAt(result.position);
  if (dot(result.normalv, result.eyev) <
      0) { // check point is inside of outside
    result.inside = true;
    result.normalv = -result.normalv;
  } else {
    result.inside = false;
  }
  result.overPoint = result.position + (result.normalv * EPSILON);

  return result;
}

} // namespace

#endif

#ifndef TEST_SHAPE_H
#define TEST_SHAPE_H

class test_shape : public shape {
public:
  std::vector<intersection> local_intersect(ray &r) {
    saved_ray = r;
    std::vector<intersection> xs;
    return xs;
  }

  vec localNormalAt(point &p) {
    vec result(0, 0, 0);
    return result;
  }

private:
};

#endif

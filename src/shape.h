#ifndef SHAPE_H
#define SHAPE_H

#include "./intersection.h"
#include "./mat.h"
#include "./material.h"
#include "./pattern.h"
#include "./point.h"
#include "./ray.h"
#include "./vec.h"

#include <vector>

class shape {
public:
  shape() {}
  virtual ~shape() {}
  void setMaterial(material n) { m = n; }
  material getMaterial() { return m; }
  void setTransform(mat m);
  mat getTransform() const { return Transform; }
  mat &getInverseTransform() { return TransformInverse; }
  std::vector<intersection> intersect(ray &r);
  vec normalAt(point &p);
  virtual std::vector<intersection> local_intersect(ray &r) = 0;
  virtual vec localNormalAt(point &p) = 0;
  color ColorAtShape(point &p);

  void setPattern(std::shared_ptr<pattern> p) { patternPtr = p; }
  void setStripePattern(color c1, color c2);
  void setStripePattern(color c1, color c2, mat &m);
  void setGradientPattern(color c1, color c2);
  void setGradientPattern(color c1, color c2, mat &m);
  void setRingPattern(color c1, color c2);
  void setRingPattern(color c1, color c2, mat &m);
  void setThreeDCheckerPattern(color c1, color c2);
  void setThreeDCheckerPattern(color c1, color c2, mat &m);

  material m;
  ray saved_ray;
  std::shared_ptr<pattern> patternPtr = nullptr;

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
  // check point is inside of outside
  if (dot(result.normalv, result.eyev) < 0) {
    result.inside = true;
    result.normalv = -result.normalv;
  } else {
    result.inside = false;
  }
  result.overPoint = result.position + (result.normalv * EPSILON);
  result.reflectv = r.direction.reflect(result.normalv);

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

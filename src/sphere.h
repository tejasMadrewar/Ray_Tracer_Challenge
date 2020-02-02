#ifndef SPHERE_H
#define SPHERE_H

#include "./intersection.h"
#include "./mat.h"
#include "./material.h"
#include "./object.h"
#include "./ray.h"
#include "./tuple.h"
#include <cmath>
#include <vector>

#define DEBUG_SPHERE 0

class sphere : public object {
public:
  sphere() : object() {}
  ~sphere() {}

  sphere(point ori, float r) {
    origin = ori;
    radius = r;
  }

  void print() {
    std::cout << "---------------\n";
    std::cout << "sphere id" << getID() << " \n";
    std::cout << "---------------\n";
    std::cout << "transform\n";
    sphereTransform.print();
    std::cout << "---------------\n";
  }

  // find intersection
  std::vector<intersection> intersect(ray r) {

    // transforming ray by inverse of sphereTransform
    r = sphereTransformInverse * r;
    std::vector<intersection> xs;
    float a, b, c, discirminant;
    vec sphere_to_ray = r.origin - point(0, 0, 0);

    a = dot(r.direction, r.direction);
    b = 2 * dot(r.direction, sphere_to_ray);
    c = dot(sphere_to_ray, sphere_to_ray) - 1;

    discirminant = (b * b) - (4 * a * c);

#if DEBUG_SPHERE
    std::cout << "\nDEBUG_SPHERE";
    std::cout << "\nr.direction ";
    r.direction.print();
    std::cout << "\nr.origin ";
    r.origin.print();
    std::cout << "\nsphere_to_ray ";
    sphere_to_ray.print();
    std::cout << "\na:" << a << " b:" << b << " c:" << c;
    std::cout << "\ndiscirminant " << discirminant;
#endif

    // ray is not hitting the sphere
    if (discirminant < 0) {
      return xs;
    }

    xs.resize(2, intersection(this));
    xs[0].intersected = (-b - sqrt(discirminant)) / (2 * a);
    xs[1].intersected = (-b + sqrt(discirminant)) / (2 * a);

    // sort
    if (xs[0].intersected > xs[1].intersected) {
      std::swap(xs[0].intersected, xs[1].intersected);
    }

#if DEBUG_SPHERE
    std::cout << "\nxs[0] " << xs[0].intersection;
    std::cout << "\nxs[1] " << xs[1].intersection;
#endif
    return xs;
  }

  // set and get sphere transform
  void setTransform(mat m) {
    sphereTransform = m;
    sphereTransformInverse = m.inverse();
  }
  mat getTransform() const { return sphereTransform; }

  // get normal at point assume point is on sphere
  vec normalAt(point &p) {
    point objPoint = sphereTransformInverse * p;
    vec normal = objPoint - origin;
    vec worldNormal = (sphereTransformInverse.transpose() * normal);
    worldNormal.setW(0);       // due to transpose
    return worldNormal.norm(); // always return normalize vector
  }

  void setMaterial(material n) { m = n; }
  material getMaterial() { return m; }

  material m;

private:
  float radius = 1;
  point origin = point(0, 0, 0);
  mat sphereTransform = mat::Identity(4);
  mat sphereTransformInverse = mat::Identity(4);
};

#endif

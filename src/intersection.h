#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "./ray.h"
#include <iostream>
#include <vector>

class shape;

#define DEBUG_INTERSECTION 0

class intersection {
public:
  shape *obj;
  float intersected;

  intersection() {
    obj = nullptr;
    intersected = 0;
  }
  intersection(shape *o) { obj = o; }
  intersection(float i, shape *o) {
    obj = o;
    intersected = i;
  }

  intersection(const intersection &i) {
    obj = i.obj;
    intersected = i.intersected;
  }

  // equality between intersection
  bool operator==(intersection &i) {
    if (this->intersected == i.intersected && this->obj == i.obj)
      return true;
    else
      return false;
  }

  // less than operator for sorting
  bool operator<(const intersection &i) {
    if (this->intersected < i.intersected)
      return true;
    else
      return false;
  }

private:
};

// structure to hold preComputed data of intersection
class preComputed {
public:
  preComputed() {}

  preComputed(preComputed &p) {
    objptr = p.objptr;
    position = p.position;
    eyev = p.eyev;
    normalv = p.normalv;
    inside = p.inside;
    overPoint = p.overPoint;
  }

  shape *objptr;
  point position;
  point overPoint;
  vec eyev;
  vec normalv;
  bool inside = false;
};

// make function global
namespace {

intersection hit(std::vector<intersection> &v) {
  // empty vector
  if (v.size() == 0)
    return intersection(0, nullptr);

  // intersection allNegative(0, nullptr);
  intersection result = v.at(0);

#if DEBUG_INTERSECTION
  std::cout << "hit intersection\n";
#endif

  for (int i = 0; i < v.size(); ++i) {

#if DEBUG_INTERSECTION
    std::cout << v[i].intersected << "\n";
#endif
    // comparison
    if (v.at(i).intersected > 0 && result.intersected > 0) {
      if (v.at(i).intersected < result.intersected) {
        result = v.at(i);
      }
    } else {
      if (v.at(i).intersected > 0)
        result = v.at(i);
    }
  }

  // check for allNegative
  if (result.intersected >= 0) {
    return result;
  } else
    return intersection(0, nullptr);
}


} // namespace

#endif

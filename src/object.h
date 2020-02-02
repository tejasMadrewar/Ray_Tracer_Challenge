#ifndef OBJECT_H
#define OBJECT_H 1

#include "./point.h"
#include "./ray.h"
#include "./vec.h"

class intersection;
class material;

namespace {

class object {
public:
  object() { id = counter++; }
  virtual ~object() {}

  int getID() { return id; }

  // virtual vec normalAt(point p){return vec(0,0,0);}
  virtual vec normalAt(point &p) = 0;                     // pure virtual
  virtual std::vector<intersection> intersect(ray r) = 0; // pure virtual
  virtual material getMaterial() = 0;                     // pure virtual
  virtual void setMaterial(material m) = 0;               // pure virtual

  void print() { std::cout << "Object with ID " << getID() << "\n"; }

private:
  int id = 0;
  static int counter;
};

int object::counter = 0;
} // namespace
#endif

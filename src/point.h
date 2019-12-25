#include "tuple.h"
#include "vec.h"

#ifndef POINT_H
#define POINT_H

class point : public tuple {
private:
public:
  point() : tuple(0, 0, 0, 1) {}
  point(float x, float y, float z) : tuple(x, y, z, 1) {}
  point(const tuple tup) {
    t[0] = tup.t[0];
    t[1] = tup.t[1];
    t[2] = tup.t[2];
  }
  ~point() {}

  void setW(float a) {}

  // point subtraction
  vec operator-(point a) {
    return vec(t[0] - a.t[0], t[1] - a.t[1], t[2] - a.t[2]);
  }

  point operator-(vec a) {
    return point(t[0] - a.t[0], t[1] - a.t[1], t[2] - a.t[2]);
  }
};

// point operator+(const vec& v, const point& p){
//	return point( v.t[0] + p.t[0], v.t[1] + p.t[1], v.t[2] + p.t[2]);
//}
//
// point operator+(const point& p, const vec& v){
//	return point( v.t[0] + p.t[0], v.t[1] + p.t[1], v.t[2] + p.t[2]);
//}

#endif

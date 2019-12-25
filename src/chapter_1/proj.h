#ifndef PROJECTILE
#define PROJECTILE

#include "../point.h"
#include "../vec.h"

class projectile {
public:
  projectile(point ip, vec iv) {
    p1 = ip;
    v1 = iv;
  }
  point position() { return p1; }
  vec velo() { return v1; }

private:
  point p1;
  vec v1;
};
#endif

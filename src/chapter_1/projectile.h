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

  projectile(const projectile& a){
	  p1 = a.p1;
	  v1 = a.v1;
  }

  point position() { return p1; }
  vec velo() { return v1; }
  void print() {
    std::cout << "\nPosition : ";
    p1.print();
    std::cout << "\nVelocity : ";
    v1.print();
  }

private:
  point p1;
  vec v1;
};
#endif

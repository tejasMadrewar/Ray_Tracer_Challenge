#ifndef ENVIRONMENT
#define ENVIRONMENT

#include "../vec.h"

class env {
public:
  env(vec igravity, vec iwind) {
    grav = igravity;
    win = iwind;
  }
  vec gravity() { return grav; }
  vec wind() { return win; }

private:
  vec grav; // gravity
  vec win;  // wind
};

#endif

#include "tick.h"

projectile tick(env en, projectile proj, float time) {
  point p1;
  vec v1;
  p1 = proj.position() + (proj.velo() * time);
  v1 = proj.velo() + (en.gravity() * time) + (en.wind() * time);

  return (projectile(p1, v1));
}

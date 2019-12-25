#include "env.h"
#include "projectile.h"
#include "tick.h"

int main() {
  projectile proj(point(0, 1, 0), vec(1, 1, 0).norm());
  env en(vec(0, -0.1, 0), vec(-0.01, 0, 0));
  proj.print();
  int i = 0;
  while (0 < proj.position().getY()) {
    std::cout << "\n" << i;
    proj = tick(en, proj, 0.5);
    // proj = tick(en, proj);
    proj.print();
    i++;
  }
  return 0;
}

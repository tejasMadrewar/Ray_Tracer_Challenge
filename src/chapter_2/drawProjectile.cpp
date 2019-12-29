#include "./drawProjectile.h"

#define DEBUG_drawProjectile 0
int drawProjectile(env en, projectile proj, canvas &c, color col, float time) {

  while (proj.position().getY() >= 0 && proj.position().getY() <= c.height() &&
         proj.position().getX() >= 0 && proj.position().getX() <= c.width()) {
    int x = proj.position().getX();
    int y = proj.position().getY();

#if DEBUG_drawProjectile
    std::cout << "x:" << proj.position().getX()
              << " y: " << proj.position().getY() << "\n";
    std::cout << "INT x:" << x << " y: " << y << "\n";
#endif

    c.write_pixel(x, c.height() - y, col);
    proj = tick(en, proj);
  }

  return 0;
}

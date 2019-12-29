#include "./drawProjectile.h"

int main() {
  std::cout << "Started plotting projectile\n";
  vec gravity(0, -0.1, 0);
  vec wind(-0.01, 0, 0);

  point start(0, 1, 0);
  vec velocity = vec(1, 1.8, 0).norm() * 11.25;

  color red(1, 0, 0);
  color green(0, 1, 0);
  color blue(0, 0, 1);
  std::vector<color> col_v;
  col_v.push_back(red);
  col_v.push_back(green);
  col_v.push_back(blue);

  env e = env(gravity, wind);
  projectile p = projectile(start, velocity);
  canvas c(900, 550);

  // plotting projectiles
  for (int i = 1; i < 5; i++) {
    color col = col_v.at(i % col_v.size());
    vec v1 = velocity / i;
    p = projectile(start, v1);
    drawProjectile(e, p, c, col);
  }

  c.canvas_to_ppm("output_trajectory.ppm");
  std::cout << "Finished plotting projectile\n";
  return 0;
}

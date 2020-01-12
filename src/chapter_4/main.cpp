#include "../canvas.h"
#include "../intersection.h"
#include "../mat.h"
#include "../point.h"
#include "../sphere.h"
#include "../transform.h"

#define DEBUG 0

int main() {
  const int canvas_size = 500;

  point rayOrigin(0, 0, -5);
  float wall_z = 10;
  float wall_size = 7;
  float half = wall_size / 2;

  float pixel_size = wall_size / canvas_size;
  sphere s;
  transform t;

  canvas c(canvas_size, canvas_size);
  color red(1, 0, 0);
  ray r(rayOrigin, vec(0, 0, 0));

  float world_x = 0;
  float world_y = 0;
  point position(0, 0, 0);
  std::vector<intersection> xs;
  intersection inter;

#if DEBUG
  std::cout << "wall_z:" << wall_z << "\n"
            << "pixel_size:" << pixel_size << "\n";
#endif

  // normal sphere
  for (int i = 0; i < c.width(); ++i) {
    world_x = half - (pixel_size * i);

    for (int j = 0; j < c.height(); ++j) {
      world_y = half - (pixel_size * j);

#if DEBUG
      std::cout << "i:" << i << " "
                << "j:" << j << " ";
      std::cout << "world_x:" << world_x << " "
                << "world_y:" << world_y << "\n";
#endif

      position = point(world_x, world_y, wall_z);
      r.direction = (position - rayOrigin).norm();

      xs = s.intersect(r);
      inter = hit(xs);

      // check if ray is hit to sphere
      if (inter.obj != nullptr) {
        c.write_pixel(i, c.height() - j, red);
      }
    }
  }

  c.canvas_to_ppm("Sphere.ppm");

  //-----------------------------------------------------
  // shrink it along y axis
  canvas c1(canvas_size,canvas_size);
  s.setTransform(t.scale(1,0.5,1));

  for (int i = 0; i < c.width(); ++i) {
    world_x = half - (pixel_size * i);

    for (int j = 0; j < c.height(); ++j) {
      world_y = half - (pixel_size * j);
      position = point(world_x, world_y, wall_z);
      r.direction = (position - rayOrigin).norm();

      xs = s.intersect(r);
      inter = hit(xs);

      // check if ray is hit to sphere
      if (inter.obj != nullptr) {
        c1.write_pixel(i, c.height() - j, red);
      }
    }
  }
  c1.canvas_to_ppm("SphereShrinkY.ppm");

  //-----------------------------------------------------
  // shrink it along x axis
  canvas c2(canvas_size,canvas_size);
  s.setTransform(t.scale(0.5,1,1));

  for (int i = 0; i < c.width(); ++i) {
    world_x = half - (pixel_size * i);

    for (int j = 0; j < c.height(); ++j) {
      world_y = half - (pixel_size * j);
      position = point(world_x, world_y, wall_z);
      r.direction = (position - rayOrigin).norm();

      xs = s.intersect(r);
      inter = hit(xs);

      if (inter.obj != nullptr) {
        c2.write_pixel(i, c.height() - j, red);
      }
    }
  }
  c2.canvas_to_ppm("SphereShrinkX.ppm");

  //-----------------------------------------------------
  // shrink it along x axis and rotate it
  canvas c3(canvas_size,canvas_size);
  s.setTransform(t.rotZ(PI/4) * t.scale(0.5,1,1));

  for (int i = 0; i < c.width(); ++i) {
    world_x = half - (pixel_size * i);

    for (int j = 0; j < c.height(); ++j) {
      world_y = half - (pixel_size * j);
      position = point(world_x, world_y, wall_z);
      r.direction = (position - rayOrigin).norm();

      xs = s.intersect(r);
      inter = hit(xs);

      if (inter.obj != nullptr) {
        c3.write_pixel(i, c.height() - j, red);
      }
    }
  }
  c3.canvas_to_ppm("SphereShrinkXrotZ.ppm");

  //-----------------------------------------------------
  // shrink it along x axis and skew it
  canvas c4(canvas_size,canvas_size);
  s.setTransform(t.shear(1,0,0,0,0,0) * t.scale(0.5,1,1));

  for (int i = 0; i < c.width(); ++i) {
    world_x = half - (pixel_size * i);

    for (int j = 0; j < c.height(); ++j) {
      world_y = half - (pixel_size * j);
      position = point(world_x, world_y, wall_z);
      r.direction = (position - rayOrigin).norm();

      xs = s.intersect(r);
      inter = hit(xs);

      if (inter.obj != nullptr) {
        c4.write_pixel(i, c.height() - j, red);
      }
    }
  }
  c4.canvas_to_ppm("SphereShrinkXSkew.ppm");
  return 0;
}

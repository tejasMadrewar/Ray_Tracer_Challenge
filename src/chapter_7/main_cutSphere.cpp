#include "../camera.h"
#include "../canvas.h"
#include "../intersection.h"
#include "../light.h"
#include "../mat.h"
#include "../plane.h"
#include "../sphere.h"
#include "../transform.h"
#include "../world.h"

#define DEBUG 0

int main() {

  // camera cam(100, 50, PI / 3);
  int scaleSmall = 1;
  camera cam(3000 / scaleSmall, 1500 / scaleSmall, PI / 3);
  transformation trans;
  point from(0, 1.5, -5);
  point to(0, 1, 0);
  vec up(0, 1, 0);
  mat cameraTrans = trans.view_transform(from, to, up);
  cam.setTransform(cameraTrans);

  mat sphereTransform(4);
  transform t;

  world w;

  // floor
  material m;
  m.col = color(1, 0.9, 0.9);
  m.specular = 0;
  sphereTransform = mat::Identity(4); // floor
  sphereTransform = t.translate(0, 0.2, 0);
  w.add_plane(sphereTransform, m);

  sphereTransform = t.translate(0, 0, 0.7) * t.rotX(PI / 2); // wall
  w.add_plane(sphereTransform, m);

  // middle
  sphereTransform = t.translate(-0.5, 1, 0.5);
  material n;
  n.col = color(0.1, 1, 0.5);
  n.diffuse = 0.7;
  n.specular = 0.3;
  w.add_sphere(sphereTransform, n);

  // right
  sphereTransform = t.translate(1.5, 0.5, -0.5) * t.scale(0.5, 0.5, 0.5);
  material o;
  o.col = color(0.5, 1, 0.1);
  o.diffuse = 0.7;
  o.specular = 0.3;
  w.add_sphere(sphereTransform, o);

  // left
  sphereTransform = t.translate(-1.5, 0.33, -0.75) * t.scale(0.33, 0.33, 0.33);
  material p;
  p.col = color(1, 0.8, 0.1);
  p.diffuse = 0.7;
  p.specular = 0.3;
  w.add_sphere(sphereTransform, p);

  // light source
  pointLight light;
  light.position = point(-10, 10, -10);
  light.intensity = color(1, 1, 1);
  w.worldLight = light;

  // canvas
  canvas c = cam.render(w);
  c.canvas_to_ppm("main_cutSphere.ppm");
}

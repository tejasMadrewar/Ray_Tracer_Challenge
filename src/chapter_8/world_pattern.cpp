#include "../camera.h"
#include "../canvas.h"
#include "../intersection.h"
#include "../light.h"
#include "../mat.h"
#include "../plane.h"
#include "../sphere.h"
#include "../transform.h"
#include "../world.h"
#include <memory>

#define DEBUG 0

int main() {
  // color for pattern
  color white(1, 1, 1), black(0, 0, 0);

  // camera cam(100, 50, PI / 3);
  // camera cam(3000, 1500, PI / 3);
  camera cam(3000 / 1, 1500 / 1, PI / 3);
  transformation trans;
  point from(0, 1.5, -5);
  point to(0, 1, 0);
  vec up(0, 1, 0);
  mat cameraTrans = trans.view_transform(from, to, up);
  cam.setTransform(cameraTrans);

  mat Trans(4);
  transform t;

  world w;

  mat patternTransform = mat::Identity(4);
  // floor
  material m;
  std::shared_ptr<shape> f(new plane());
  m.col = color(1, 0.9, 0.9);
  m.specular = 0;
  Trans = t.scale(10, 0.01, 10);
  f->setTransform(Trans);
  f->setMaterial(m);
  patternTransform = t.scale(0.2,0.2,0.2);
  f->setThreeDCheckerPattern(color(0.1, 0.2, 0.3), color(1, 0.9, 0.9),patternTransform);
  w.add_shape(f);

  // middle
  Trans = t.translate(-0.5, 1, 0.5);
  material n;
  n.col = color(0.1, 1, 0.5);
  n.diffuse = 0.7;
  n.specular = 0.3;
  std::shared_ptr<shape> s1(new sphere());
  s1->setMaterial(n);
  s1->setTransform(Trans);
  patternTransform = t.scale(0.2,0.2,0.2) * t.rotY(PI/4) * t.rotZ(PI/4);
  s1->setStripePattern(color(1,0.8,0.1), color(0.1,1,0.5),patternTransform);
  w.add_shape(s1);
  

  // right
  Trans = t.translate(1.5, 0.5, -0.5) * t.scale(0.5, 0.5, 0.5);
  material o;
  o.col = color(0.5, 1, 0.1);
  o.diffuse = 0.7;
  o.specular = 0.3;
  std::shared_ptr<shape> s2(new sphere());
  s2->setMaterial(o);
  s2->setTransform(Trans);
  patternTransform = t.scale(0.6,0.6,0.6) * t.rotY(PI/4);
  s2->setGradientPattern(color(1,0.8,0.1), o.col,patternTransform);
  w.add_shape(s2);
  //w.add_sphere(Trans, o);

  // left
  Trans = t.translate(-1.5, 0.33, -0.75) * t.scale(0.33, 0.33, 0.33);
  material p;
  p.col = color(1, 0.8, 0.1);
  p.diffuse = 0.7;
  p.specular = 0.3;
  std::shared_ptr<shape> s3(new sphere());
  s3->setMaterial(o);
  s3->setTransform(Trans);
  patternTransform = t.scale(0.1,0.1,0.1) * t.rotY(PI/4);
  s3->setThreeDCheckerPattern(o.col, p.col,patternTransform);
  w.add_shape(s3);
  //w.add_sphere(Trans, p);

  // light source
  pointLight light;
  light.position = point(-10, 10, -10);
  light.intensity = color(1, 1, 1);
  w.worldLight = light;

  // canvas
  canvas c = cam.render(w);
  c.canvas_to_ppm("world_pattern.ppm");
}

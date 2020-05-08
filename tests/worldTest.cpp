#include "../src/world.h"
#include "../src/intersection.h"
#include "catch2/catch.hpp"
#include <memory>

TEST_CASE("WORLD DEFAULT CONSTRUCTOR", "[single-file][world]") {
  world w = world::default_world();

  REQUIRE(1 == 1);
}

TEST_CASE("INTERSECT A WORLD WITH A RAY", "[single-file][world]") {
  world w = world::default_world();
  ray r(point(0, 0, -5), vec(0, 0, 1));
  std::vector<intersection> xs = w.intersect_world(r);

  REQUIRE(xs.size() == 4);
  REQUIRE(xs[0].intersected == 4);
  REQUIRE(xs[1].intersected == 4.5);
  REQUIRE(xs[2].intersected == 5.5);
  REQUIRE(xs[3].intersected == 6);
}

TEST_CASE("SHADING AN INTERSECTION", "[single-file][world]") {
  world w = world::default_world();
  material m;
  ray r(point(0, 0, -5), vec(0, 0, 1));
  preComputed p;
  sphere s1;

  m.col = color(0.8, 1.0, 0.6);
  m.diffuse = 0.7;
  m.specular = 0.2;
  s1.setMaterial(m);

  // intersection i(4, w.sVec.at(0)); // first object
  intersection i(4, w.vecShapes.at(0)); // first object
  p = prepareComputation(i, r);

  color result = w.shadeHit(p);
  color answer(0.38066, 0.47583, 0.2855);

  REQUIRE((result == answer) == true);
}

TEST_CASE("SHADING AN INTERSECTION FROM THE INSIDE", "[single-file][world]") {
  world w = world::default_world();
  transform t;
  preComputed p;
  sphere s2;
  ray r(point(0, 0, 0), vec(0, 0, 1));

  w.worldLight.position = point(0, 0.25, 0);
  w.worldLight.intensity = color(1, 1, 1);
  s2.setTransform(t.scale(0.5, 0.5, 0.5));

  intersection i(0.5, w.vecShapes.at(1)); // with second object

  p = prepareComputation(i, r);

  color result = w.shadeHit(p);
  // color answer(0.90498, 0.90498, 0.90498);
  // changed after shadadows are added
  color answer(0.904662, 0.904662, 0.904662);

  REQUIRE((result == answer) == true);
}

TEST_CASE("THE COLOR WHEN A RAY MISSES", "[single-file][world]") {
  world w = world::default_world();
  ray r(point(0, 0, -5), vec(0, 1, 0));
  color result, answer(0, 0, 0);
  result = w.colorAt(r);

  REQUIRE((result == answer) == true);
}

TEST_CASE("THE COLOR WHEN A RAY HITS", "[single-file][world]") {
  world w = world::default_world();
  ray r(point(0, 0, -5), vec(0, 0, 1));
  color result, answer(0.38066, 0.47583, 0.2855);
  result = w.colorAt(r);

  REQUIRE((result == answer) == true);
}

TEST_CASE("THE COLOR WITH AN INTERSECTION BEHIND THE RAY",
          "[single-file][world]") {
  world w = world::default_world();
  ray r(point(0, 0, 0.75), vec(0, 0, -1));
  sphere *s = (sphere *)w.vecShapes.at(0).get();
  s->m.ambient = 1;
  s = (sphere *)w.vecShapes.at(1).get();
  s->m.ambient = 1;

  color result, answer;
  answer = s->m.col;
  result = w.colorAt(r);

  REQUIRE((result == answer) == true);
}

TEST_CASE("THERE IS NO SHADOW WHEN NOTHING IS COLLINER WITH POINT AND LIGHT",
          "[single-file][world]") {
  world w = world::default_world();
  point p(0, 10, 0);
  REQUIRE(w.isShadowed(p) == false);
}

TEST_CASE("THE SHADOW WHEN AN OBJECT IS BETWEEN THE POINT AND THE LIGHT",
          "[single-file][world]") {
  world w = world::default_world();
  point p(10, -10, 10);
  REQUIRE(w.isShadowed(p) == true);
}

TEST_CASE("THERE IS NO SHADOW WHEN AN OBJECT IS BEHIND THE LIGHT",
          "[single-file][world]") {
  world w = world::default_world();
  point p(-20, 20, -20);
  REQUIRE(w.isShadowed(p) == false);
}

TEST_CASE("THERE IS NO SHADOW WHEN AN OBJECT IS BEHIND THE POINT",
          "[single-file][world]") {
  world w = world::default_world();
  point p(-2, 2, -2);
  REQUIRE(w.isShadowed(p) == false);
}

TEST_CASE("shade_hit() IS GIVEN AN INTERSECTION IN SHADOW",
          "[single-file][world]") {
  world w;
  transform t;
  mat matrix = mat::Identity(4);
  ray r(point(0, 0, 5), vec(0, 0, 1));

  pointLight l;
  l.position = point(0, 0, -10);
  l.intensity = color(1, 1, 1);
  w.worldLight = l;

  w.add_sphere(matrix);
  w.add_sphere(t.translate(0, 0, 10));

  intersection i(4, w.vecShapes.at(1));
  preComputed pre;
  pre = prepareComputation(i, r);
  color c = w.shadeHit(pre);

  REQUIRE((c == color(0.1, 0.1, 0.1)) == true);
}

TEST_CASE("The reflected color for a nonreflective material",
          "[single-file][world]") {
  world w = w.default_world();
  ray r(point(0, 0, 0), vec(0, 0, 1));

  std::shared_ptr<shape> s = w.vecShapes.at(1);
  (*s).m.ambient = 1;

  intersection i(1, s);

  preComputed pre;
  pre = prepareComputation(i, r);
  color c = w.reflectedColorAt(pre);

  REQUIRE((c == color(0, 0, 0)) == true);
}

TEST_CASE("The reflected color for a reflective material",
          "[single-file][world]") {
  world w = w.default_world();
  ray r(point(0, 0, -3), vec(0, -sqrt(2) / 2, sqrt(2) / 2));
  color c;
  preComputed p;
  std::shared_ptr<shape> s(new plane);
  (*s).m.reflective = 0.5;
  transform t;
  (*s).setTransform(t.translate(0, -1, 0));
  w.add_shape(s);
  intersection i(sqrt(2), s);

  p = prepareComputation(i, r);
  c = w.reflectedColorAt(p);

  REQUIRE((c == color(0.19032, 0.2379, 0.14274)) == true);
}

TEST_CASE("shadeHit() with a reflective material", "[single-file][world]") {
  world w = w.default_world();
  ray r(point(0, 0, -3), vec(0, -sqrt(2) / 2, sqrt(2) / 2));
  color c;
  transform t;
  preComputed p;
  std::shared_ptr<shape> s(new plane);
  (*s).m.reflective = 0.5;
  (*s).setTransform(t.translate(0, -1, 0));
  w.add_shape(s);
  intersection i(sqrt(2), s);

  p = prepareComputation(i, r);
  c = w.shadeHit(p);

  REQUIRE((c == color(0.87677, 0.92436, 0.82918)) == true);
}

TEST_CASE("colorAt() with a mutually reflective material",
          "[single-file][world]") {
  world w;
  ray r(point(0, 0, 0), vec(0, 1, 0));
  pointLight l;
  l.intensity = color(1, 1, 1);
  l.position = point(0, 0, 0);
  w.worldLight = l;
  transform t;

  std::shared_ptr<shape> pl(new plane);
  (*pl).m.reflective = 1;
  (*pl).setTransform(t.translate(0, -1, 0));
  w.add_shape(pl);

  std::shared_ptr<shape> pu(new plane);
  (*pu).m.reflective = 1;
  (*pu).setTransform(t.translate(0, 1, 0));
  w.add_shape(pu);

  // colorAt should terminate successfully
  color result = w.colorAt(r);

  REQUIRE((1 == 1) == true);
}

TEST_CASE("The reflected colot at the maximum recursive depth",
          "[single-file][world]") {
  world w = world::default_world();
  transform t;
  ray r(point(0, 0, -3), vec(0, -sqrt(2) / 2, sqrt(2) / 2));
  std::shared_ptr<shape> p(new plane);
  (*p).m.reflective = 0.5;
  (*p).setTransform(t.translate(0, -1, 0));

  w.add_shape(p);
  intersection i(sqrt(2), p);
  preComputed pre;
  pre = prepareComputation(i, r);
  color c = w.reflectedColorAt(pre, 0);

  REQUIRE((c == color(0, 0, 0)) == true);
}

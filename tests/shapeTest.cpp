#include "../src/shape.h"
#include "../src/sphere.h"
#include "../src/transform.h"

#include "catch2/catch.hpp"

TEST_CASE("THE DEFAULT TRANSFORMATION", "[single-file][shape]") {
  test_shape sh;
  mat m = mat::Identity(4);

  REQUIRE((sh.getTransform() == m) == true);
}

TEST_CASE("ASSIGNING A TRANSFORMATION", "[single-file][shape]") {
  test_shape sh;
  transform t;
  mat m = t.translate(2, 3, 4);
  sh.setTransform(m);

  REQUIRE((sh.getTransform() == m) == true);
}

TEST_CASE("THE DEFAULT MATERIAL", "[single-file][shape]") {
  test_shape sh;
  material m;

  REQUIRE((sh.getMaterial() == m) == true);
}

TEST_CASE("ASSIGNING MATERIAL", "[single-file][shape]") {
  test_shape sh;
  material m;
  m.ambient = 1;
  sh.setMaterial(m);

  REQUIRE((sh.getMaterial() == m) == true);
}

TEST_CASE("INTERSECTING A SCALED SHAPE WITH A RAY",
          "[single-file][sphere][shape]") {
  test_shape s;
  transform t;
  ray r(point(0, 0, -5), vec(0, 0, 1));

  s.setTransform(t.scale(2, 2, 2));
  std::vector<intersection> xs = s.intersect(r);

  REQUIRE((s.saved_ray.origin == point(0, 0, -2.5)) == true);
  REQUIRE((s.saved_ray.direction == vec(0, 0, 0.5)) == true);
}

TEST_CASE("INTERSECTING A TRANSLATED SHAPE WITH A RAY",
          "[single-file][sphere][shape]") {
  test_shape s;
  transform t;
  ray r(point(0, 0, -5), vec(0, 0, 1));

  s.setTransform(t.translate(5, 0, 0));
  std::vector<intersection> xs = s.intersect(r);

  REQUIRE((s.saved_ray.origin == point(-5, 0, -5)) == true);
  REQUIRE((s.saved_ray.direction == vec(0, 0, 1)) == true);
}

TEST_CASE("COMPUTING THE NORMAL ON A TRANSLATED SHAPE",
          "[single-file][sphere][shape]") {
  sphere s;
  transform t;
  s.setTransform(t.translate(0, 1, 0));
  vec n;
  point p(0, 1.70711, -0.70711);

  n = s.normalAt(p);

  REQUIRE((n == vec(0, 0.70711, -0.70711)) == true);
}

TEST_CASE("COMPUTING THE NORMAL ON A TRANSFORMED SHAPE",
          "[single-file][sphere][shape]") {
  sphere s;
  transform t;
  vec n;
  point p(0, sqrt(2) / 2, -sqrt(2) / 2);
  mat m(4);
  m = t.scale(1, 0.5, 1) * t.rotZ(PI / 5);
  s.setTransform(m);

  n = s.normalAt(p);

  REQUIRE((n == vec(0, 0.97014, -0.24254)) == true);
}

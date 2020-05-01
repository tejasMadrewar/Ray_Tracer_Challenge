#include "../src/transform.h"
#include "../src/mat.h"
#include "../src/point.h"
#include "../src/tuple.h"
#include "../src/vec.h"
#include "catch2/catch.hpp"
//#include <corecrt_math.h>

TEST_CASE("Testing TRANSFORM translate", "[single-file][transform]") {
  transform t;
  point p(-3, 4, 5);
  point ans(2, 1, 7);
  point ans2(-8, 7, 3);
  vec v1(-3, 4, 5);

  // multiply by a translation matrix
  REQUIRE((t.translate(5, -3, 2) * p == ans) == true);

  // multiply by the inverse of a translation matrix
  REQUIRE((t.translate(5, -3, 2).inverse() * p == ans2) == true);

  // translation does not affect vectors
  REQUIRE((t.translate(5, -3, 2) * v1 == v1) == true);
}

TEST_CASE("Testing TRANSFORM scaling", "[single-file][transform]") {
  transform t;
  point p(-4, 6, 8), q(2, 3, 4);
  vec v(-4, 6, 8);

  // multiply a scaling matrix with point
  REQUIRE((t.scale(2, 3, 4) * p == point(-8, 18, 32)) == true);

  // multiply a scaling matrix with vector
  REQUIRE((t.scale(2, 3, 4) * v == vec(-8, 18, 32)) == true);

  // multiply by inverse of scaling matrix
  REQUIRE((t.scale(2, 3, 4).inverse() * v == vec(-2, 2, 2)) == true);

  // reflection is scaling by negative value
  REQUIRE((t.scale(-1, 1, 1) * q == point(-2, 3, 4)) == true);
}

TEST_CASE("Testing ROTATE around X AXIS (left hand rule)",
          "[single-file][transform]") {
  transform t;
  point p(0, 1, 0);
  point ans1(0, sqrt(2) / 2, sqrt(2) / 2);

  // half quarter
  REQUIRE((t.rotX(PI / 4) * p == ans1) == true);
  // full quarter
  REQUIRE((t.rotX(PI / 2) * p == point(0, 0, 1)) == true);
}

TEST_CASE("Testing ROTATE around Y AXIS (left hand rule)",
          "[single-file][transform]") {
  transform t;
  point p(0, 0, 1);
  point ans1(sqrt(2) / 2, 0, sqrt(2) / 2);

  // half quarter
  REQUIRE((t.rotY(PI / 4) * p == ans1) == true);
  // full quarter
  REQUIRE((t.rotY(PI / 2) * p == point(1, 0, 0)) == true);
}

TEST_CASE("Testing ROTATE around Z AXIS (left hand rule)",
          "[single-file][transform]") {
  transform t;
  point p(0, 1, 0);
  point ans1(-sqrt(2) / 2, sqrt(2) / 2, 0);

  // half quarter
  REQUIRE((t.rotZ(PI / 4) * p == ans1) == true);
  // full quarter
  REQUIRE((t.rotZ(PI / 2) * p == point(-1, 0, 0)) == true);
}

TEST_CASE("Testing SHEARING", "[single-file][transform]") {
  transform t;
  point p(2, 3, 4);

  // move x in proportion to y
  REQUIRE((t.shear(1, 0, 0, 0, 0, 0) * p == point(5, 3, 4)) == true);

  // move x in proportion to z
  REQUIRE((t.shear(0, 1, 0, 0, 0, 0) * p == point(6, 3, 4)) == true);

  // move y in proportion to x
  REQUIRE((t.shear(0, 0, 1, 0, 0, 0) * p == point(2, 5, 4)) == true);

  // move y in proportion to z
  REQUIRE((t.shear(0, 0, 0, 1, 0, 0) * p == point(2, 7, 4)) == true);

  // move z in proportion to x
  REQUIRE((t.shear(0, 0, 0, 0, 1, 0) * p == point(2, 3, 6)) == true);

  // move z in proportion to y
  REQUIRE((t.shear(0, 0, 0, 0, 0, 1) * p == point(2, 3, 7)) == true);
}

TEST_CASE("Testing Chaining Transformation", "[single-file][transform]") {
  transform t;
  point p(1, 0, 1);
  mat A = t.rotX(PI / 2);
  mat B = t.scale(5, 5, 5);
  mat C = t.translate(10, 5, 7);

  // individual transformation are applied in sequence
  point p1 = A * p;
  point p2 = B * p1;
  point p3 = C * p2;

  // rotation
  REQUIRE((p1 == point(1, -1, 0)) == true);
  // scaling
  REQUIRE((p2 == point(5, -5, 0)) == true);
  // translation
  REQUIRE((p3 == point(15, 0, 7)) == true);

  // all transformation in revers order
  mat D = C * B * A;
  REQUIRE((D * p == point(15, 0, 7)) == true);
}

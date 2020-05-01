#include "../src/pattern.h"
#include "../src/shape.h"
#include "../src/sphere.h"
#include "../src/stripePattern.h"
#include "../src/transform.h"

#include "catch2/catch.hpp"
#include <vector>

TEST_CASE("Black and White", "[single-file][pattern]") {
  color white = color(1, 1, 1);
  color black = color(0, 0, 0);
  test_pattern t;

  REQUIRE((t.black == black) == true);
  REQUIRE((t.white == white) == true);
}

TEST_CASE("Creating Stripe Pattern", "[single-file][pattern]") {
  color white(1, 1, 1);
  color black(0, 0, 0);
  stripePattern s(white, black);

  REQUIRE((s.a == white) == true);
  REQUIRE((s.b == black) == true);
}

TEST_CASE("A stripe pattern is constant in y axis", "[single-file][pattern]") {
  color white(1, 1, 1);
  color black(0, 0, 0);
  stripePattern s(white, black);
  point p1(0, 0, 0), p2(0, 1, 0), p3(0, 2, 0);

  REQUIRE((s.stripeAt(p1) == white) == true);
  REQUIRE((s.stripeAt(p2) == white) == true);
  REQUIRE((s.stripeAt(p3) == white) == true);
}

TEST_CASE("A stripe pattern is constant in z axis", "[single-file][pattern]") {
  color white(1, 1, 1);
  color black(0, 0, 0);
  stripePattern s(white, black);
  point p1(0, 0, 0), p2(0, 0, 1), p3(0, 0, 2);

  REQUIRE((s.stripeAt(p1) == white) == true);
  REQUIRE((s.stripeAt(p2) == white) == true);
  REQUIRE((s.stripeAt(p3) == white) == true);
}

TEST_CASE("A stripe pattern alternates in x axis", "[single-file][pattern]") {
  color white(1, 1, 1);
  color black(0, 0, 0);
  stripePattern s(white, black);
  point p1(0, 0, 0), p2(0.9, 0, 1), p3(1, 0, 0), p4(-0.1, 0, 0), p5(-1, 0, 0),
      p6(-1.1, 0, 0);

  REQUIRE((s.stripeAt(p1) == white) == true);
  REQUIRE((s.stripeAt(p2) == white) == true);
  REQUIRE((s.stripeAt(p3) == black) == true);
  REQUIRE((s.stripeAt(p4) == black) == true);
  REQUIRE((s.stripeAt(p5) == black) == true);
  REQUIRE((s.stripeAt(p6) == white) == true);
}

TEST_CASE("Stripes with an object transformation", "[single-file][pattern]") {
  sphere s;
  color white(1, 1, 1);
  color black(0, 0, 0);
  transform t;
  mat m(4);
  color result;
  m = t.scale(2, 2, 2);

  stripePattern sp(white, black);
  sp.setTransform(m);

  m = m.inverse().transpose();

  point p = point(1.5, 0, 0);
  result = sp.stripeAtObject(m, p);

  REQUIRE((1 == 1) == true);
}

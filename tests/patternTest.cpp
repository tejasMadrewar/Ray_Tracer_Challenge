#include "../src/pattern.h"
#include "../src/shape.h"
#include "../src/sphere.h"
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

  s.setTransform(m);
  s.setStripePattern(white, black);
  point p = point(1.5, 0, 0);

  result = s.ColorAtShape(p);

  REQUIRE((result == white) == true);
}

TEST_CASE("Stripes with a pattern transformation", "[single-file][pattern]") {
  sphere s;
  color white(1, 1, 1);
  color black(0, 0, 0);
  transform t;
  mat m(4);
  color result;
  m = t.scale(2, 2, 2);

  s.setStripePattern(white, black, m);
  point p = point(1.5, 0, 0);

  result = s.ColorAtShape(p);

  REQUIRE((result == white) == true);
}

TEST_CASE("Stripes with both ann object and a pattern transformation",
          "[single-file][pattern]") {
  sphere s;
  color white(1, 1, 1);
  color black(0, 0, 0);
  transform t;
  mat m(4);
  color result;
  point p = point(2.5, 0, 0);

  m = t.scale(2, 2, 2);
  s.setTransform(m);

  m = t.translate(0.5, 0, 0);
  s.setStripePattern(white, black, m);

  result = s.ColorAtShape(p);

  REQUIRE((result == white) == true);
}

TEST_CASE("A gradient lineraly interpolate between colors",
          "[single-file][pattern]") {
  sphere s;
  color white(1, 1, 1);
  color black(0, 0, 0);
  transform t;
  mat m(4);
  color result;
  point p1 = point(0, 0, 0);
  point p2 = point(0.25, 0, 0);
  point p3 = point(0.5, 0, 0);
  point p4 = point(0.75, 0, 0);

  color c2(0.75, 0.75, 0.75);
  color c3(0.5, 0.5, 0.5);
  color c4(0.25, 0.25, 0.25);

  s.setGradientPattern(white, black);

  result = s.ColorAtShape(p1);
  REQUIRE((result == white) == true);

  result = s.ColorAtShape(p2);
  REQUIRE((result == c2) == true);

  result = s.ColorAtShape(p3);
  REQUIRE((result == c3) == true);

  result = s.ColorAtShape(p4);
  REQUIRE((result == c4) == true);
}

TEST_CASE("A ring should extend in both x and z [ring pattern]",
          "[single-file][pattern]") {
  sphere s;
  color white(1, 1, 1);
  color black(0, 0, 0);
  transform t;
  mat m(4);
  color result;
  point p1 = point(0, 0, 0);
  point p2 = point(1, 0, 0);
  point p3 = point(0, 0, 1);
  point p4 = point(0.708, 0, 0.708);

  s.setRingPattern(white, black);

  result = s.ColorAtShape(p1);
  REQUIRE((result == white) == true);

  result = s.ColorAtShape(p2);
  REQUIRE((result == black) == true);

  result = s.ColorAtShape(p3);
  REQUIRE((result == black) == true);

  result = s.ColorAtShape(p4);
  REQUIRE((result == black) == true);
}

TEST_CASE("Checker should repeat in x [3d checker pattern]",
          "[single-file][pattern]") {
  sphere s;
  color white(1, 1, 1);
  color black(0, 0, 0);
  transform t;
  mat m(4);
  color result;
  point p1 = point(0, 0, 0);
  point p2 = point(0.99, 0, 0);
  point p3 = point(1.01, 0, 0);

  s.setThreeDCheckerPattern(white, black);

  result = s.ColorAtShape(p1);
  REQUIRE((result == white) == true);

  result = s.ColorAtShape(p2);
  REQUIRE((result == white) == true);

  result = s.ColorAtShape(p3);
  // if(result == white ) std::cout << "white\n"; else std::cout << "black\n";
  REQUIRE((result == black) == true);
}

TEST_CASE("Checker should repeat in y [3d checker pattern]",
          "[single-file][pattern]") {
  sphere s;
  color white(1, 1, 1);
  color black(0, 0, 0);
  transform t;
  mat m(4);
  color result;
  point p1 = point(0, 0, 0);
  point p2 = point(0, 0.99, 0);
  point p3 = point(0, 1.01, 0);

  s.setThreeDCheckerPattern(white, black);

  result = s.ColorAtShape(p1);
  REQUIRE((result == white) == true);

  result = s.ColorAtShape(p2);
  REQUIRE((result == white) == true);

  result = s.ColorAtShape(p3);
  // if(result == white ) std::cout << "white\n"; else std::cout << "black\n";
  REQUIRE((result == black) == true);
}

TEST_CASE("Checker should repeat in z [3d checker pattern]",
          "[single-file][pattern]") {
  sphere s;
  color white(1, 1, 1);
  color black(0, 0, 0);
  transform t;
  mat m(4);
  color result;
  point p1 = point(0, 0, 0);
  point p2 = point(0, 0, 0.99);
  point p3 = point(0, 0, 1.01);

  s.setThreeDCheckerPattern(white, black);

  result = s.ColorAtShape(p1);
  REQUIRE((result == white) == true);

  result = s.ColorAtShape(p2);
  REQUIRE((result == white) == true);

  result = s.ColorAtShape(p3);
  // if(result == white ) std::cout << "white\n"; else std::cout << "black\n";
  REQUIRE((result == black) == true);
}

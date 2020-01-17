#include "../src/tuple.h"
#include "../src/canvas.h"
#include "../src/color.h"
#include "../src/mat.h"
#include "../src/point.h"
#include "../src/vec.h"
#include "catch2/catch.hpp"

TEST_CASE("TUPLE CONSTRUCTOR and accesing values", "[single-file][tuple]") {
  tuple a = tuple();
  tuple b = tuple(1, 2, 3, 0);
  tuple c = tuple(1, 2, 3, 1);
  REQUIRE(a.getX() == 0);
  REQUIRE(a.getY() == 0);
  REQUIRE(a.getZ() == 0);
  REQUIRE(a.getW() == 0);

  REQUIRE(b.getX() == 1);
  REQUIRE(b.getY() == 2);
  REQUIRE(b.getZ() == 3);
  REQUIRE(b.getW() == 0);

  // point
  REQUIRE(b.isPoint() == false);
  REQUIRE(b.isVector() == true);
  // vector
  REQUIRE(c.isPoint() == true);
  REQUIRE(c.isVector() == false);
}

TEST_CASE("Testing POINT CONSTRUCTOR", "[single-file][point]") {
  point a = point();
  point b = point(1, 2, 3);
  REQUIRE(a.getX() == 0);
  REQUIRE(a.getY() == 0);
  REQUIRE(a.getZ() == 0);
  REQUIRE(a.getW() == 1);

  REQUIRE(b.getX() == 1);
  REQUIRE(b.getY() == 2);
  REQUIRE(b.getZ() == 3);
  REQUIRE(b.getW() == 1);

  // point
  REQUIRE(b.isPoint() == true);
  REQUIRE(b.isVector() == false);
}

TEST_CASE("Testing VECTOR CONSTRUCTOR", "[single-file][vector]") {
  vec a = vec();
  vec b = vec(1, 2, 3);
  REQUIRE(a.getX() == 0);
  REQUIRE(a.getY() == 0);
  REQUIRE(a.getZ() == 0);
  REQUIRE(a.getW() == 0);

  REQUIRE(b.getX() == 1);
  REQUIRE(b.getY() == 2);
  REQUIRE(b.getZ() == 3);
  REQUIRE(b.getW() == 0);

  // point
  REQUIRE(b.isPoint() == false);
  REQUIRE(b.isVector() == true);
}

TEST_CASE("Testing COMPARISION of TUPLE", "[single-file][tuple]") {
  tuple a = tuple(4.3, -4.2, 3.1, 1.0);
  tuple b = tuple(4.3, -4.2, 3.1, 1.0);
  tuple c = tuple(4.3, -4.1, 3.1, 1.0);
  REQUIRE((a == b) == true);
  REQUIRE((a == c) == false);
}

TEST_CASE("Testing COMPARISION oF TUPLE with VECTOR",
          "[single-file][tuple][vector]") {
  tuple a = tuple(4.3, -4.2, 3.1, 0.0);
  vec b = vec(4.3, -4.2, 3.1);
  vec d = vec(4.3, -4.1, 3.1);
  vec e = vec(4.3, -4.1, 3.1);

  // tuple vector
  REQUIRE((a == b) == true);
  REQUIRE((b == a) == true);

  // vector vector
  REQUIRE((b == d) == false);
  REQUIRE((d == b) == false);
  REQUIRE((e == d) == true);
  REQUIRE((d == e) == true);
}

TEST_CASE("Testing COMPARISION of TUPLE with POINT",
          "[single-file][tuple][point]") {
  tuple a = tuple(4.3, -4.2, 3.1, 1.0);
  point b = point(4.3, -4.2, 3.1);
  point d = point(4.3, -4.1, 3.1);
  point e = point(4.3, -4.1, 3.1);

  // tuple point
  REQUIRE((a == b) == true);
  REQUIRE((b == a) == true);

  // point point
  REQUIRE((b == d) == false);
  REQUIRE((d == b) == false);
  REQUIRE((e == d) == true);
  REQUIRE((d == e) == true);
}

TEST_CASE("Testing COMPARISION of VECTOR with POINT",
          "[single-file][vector][point]") {
  vec a = vec(4.3, -4.2, 3.1);
  point b = point(4.3, -4.2, 3.1);

  // vec point
  REQUIRE((a == b) == false);
  REQUIRE((b == a) == false);
}

TEST_CASE("Testing ADDITION of TUPLE ", "[single-file][tuple]") {
  tuple a = tuple(3, -2, 5, 1);
  tuple b = tuple(-2, 3, 1, 0);
  tuple c = tuple(1, 1, 6, 1);
  tuple d = tuple(1, 1, 7, 1);

  // addition test
  REQUIRE(((a + b) == c) == true);
  REQUIRE(((a + b) == d) == false);
}

TEST_CASE("Testing SUBTRACTION of TUPLE ", "[single-file][tuple]") {
  tuple a = tuple(3, 2, 1, 1);
  tuple b = tuple(5, 3, 7, 1);
  tuple c = tuple(-2, -1, -6, 0);
  tuple d = tuple(1, 1, 7, 1);

  // SUBTRACTION test
  REQUIRE(((a - b) == c) == true);
  REQUIRE(((a - b) == d) == false);
}

TEST_CASE("Testing SUBTRACTION of POINT ", "[single-file][point]") {
  point a = point(3, 2, 1);
  point b = point(5, 6, 7);
  vec c = vec(-2, -4, -6);
  vec d = vec(2, -4, -6);

  // SUBTRACTION test
  REQUIRE(((a - b) == c) == true);
  REQUIRE(((a - b) == d) == false);
}

TEST_CASE("Testing SUBTRACTION of POINT - VECTOR ",
          "[single-file][point][vector]") {
  point a = point(3, 2, 1);
  vec b = vec(5, 6, 7);
  point c = point(-2, -4, -6);
  point d = point(2, -4, -6);

  // SUBTRACTION test
  REQUIRE(((a - b) == c) == true);
  REQUIRE(((a - b) == d) == false);
}

TEST_CASE("Testing SUBTRACTION of VECTOR - VECTOR ", "[single-file][vector]") {
  vec a = vec(3, 2, 1);
  vec b = vec(5, 6, 7);
  vec c = vec(-2, -4, -6);
  vec d = vec(2, -4, -6);

  // SUBTRACTION test
  REQUIRE(((a - b) == c) == true);
  REQUIRE(((a - b) == d) == false);
}

TEST_CASE("Testing NEGATING TUPLE", "[single-file][tuple]") {
  tuple a = tuple(1, -2, 3, -4);
  tuple b = tuple(-1, 2, -3, 4);
  tuple c = tuple(-1, -2, -3, 4);

  // Negation test
  REQUIRE((-a == b) == true);
  REQUIRE((a == -b) == true);
  REQUIRE((-a == c) == false);
}

TEST_CASE("Testing NEGATING VECTOR", "[single-file][vector]") {
  vec a = vec(1, -2, 3);
  vec b = vec(-1, 2, -3);
  vec c = vec(-1, -2, -3);

  // Negation test
  REQUIRE((-a == b) == true);
  REQUIRE((a == -b) == true);
  REQUIRE((-a == c) == false);
}

TEST_CASE("Testing Scalar MULTIPLICATION with TUPLE", "[single-file][tuple]") {
  tuple a = tuple(1, -2, 3, -4);
  tuple b = tuple(3.5, -7, 10.5, -14);
  tuple c = tuple(0.5, -1, 1.5, -2);

  // scalar multiplication test
  REQUIRE(((a * 3.5) == b) == true);
  REQUIRE(((a * 0.5) == c) == true);
}

TEST_CASE("Testing Scalar DIVIDING with TUPLE", "[single-file][tuple]") {
  tuple a = tuple(1, -2, 3, -4);
  tuple b = tuple(0.5, -1, 1.5, -2);

  // scalar divison test
  REQUIRE(((a / 2) == b) == true);
}

TEST_CASE("Testing MAGNITUDE with TUPLE", "[single-file][tuple]") {
  vec a = vec(1, 0, 0);
  vec b = vec(0, 1, 0);
  vec c = vec(0, 0, 1);
  vec d = vec(1, 2, 3);
  vec e = vec(-1, -2, -3);

  REQUIRE(a.mag() == 1);
  REQUIRE(b.mag() == 1);
  REQUIRE(c.mag() == 1);
  REQUIRE(d.mag() == Approx(sqrt(14)));
  REQUIRE(e.mag() == Approx(sqrt(14)));
}

TEST_CASE("Testing NORMALIZATION with TUPLE", "[single-file][tuple]") {
  vec a = vec(4, 0, 0);
  vec an = a.norm();
  vec ann = vec(1, 0, 0);
  vec annf = vec(1, 0, 3);
  vec b = vec(1, 2, 3);
  vec bn = b.norm();
  vec bnn = vec(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14));
  vec bnnf = vec(1 / sqrt(15), 2 / sqrt(34), 3 / sqrt(14));

  REQUIRE((an == ann) == true);
  REQUIRE((bn == bnn) == true);

  REQUIRE((an == annf) == false);
  REQUIRE((bn == bnnf) == false);
}

TEST_CASE("Testing DOT PRODUCT with VECTOR", "[single-file][vector]") {
  vec a = vec(1, 2, 3);
  vec b = vec(2, 3, 4);

  REQUIRE(dot(a, b) == Approx(20));
}

TEST_CASE("Testing CROSS PRODUCT with VECTOR", "[single-file][vector]") {
  vec a = vec(1, 2, 3);
  vec b = vec(2, 3, 4);

  REQUIRE((cross(a, b) == vec(-1, 2, -1)) == true);
  REQUIRE((cross(b, a) == vec(1, -2, 1)) == true);
  REQUIRE((cross(b, a) == vec(1, 2, 1)) == false);
}

TEST_CASE("Testing COLOR CONSTRUCTOR", "[single-file][color]") {
  color a = color(-0.5, 0.4, 1.7);

  REQUIRE(a.red() == Approx(-0.5));
  REQUIRE(a.green() == Approx(0.4));
  REQUIRE(a.blue() == Approx(1.7));
}

TEST_CASE("Testing COLOR ADDITION", "[single-file][color]") {
  color a = color(0.9, 0.6, 0.75);
  color b = color(0.7, 0.1, 0.25);
  color an = color(1.6, 0.7, 1.0);
  color c = a + b;

  REQUIRE((c == an) == true);
}

TEST_CASE("Testing COLOR MULTIPLICATION by Scalar", "[single-file][color]") {
  color a = color(0.2, 0.3, 0.4);
  color b = a * 2;
  color an = color(0.4, 0.6, 0.8);

  REQUIRE((b == an) == true);
}

TEST_CASE("Testing COLOR MULTIPLICATION by COLOR", "[single-file][color]") {
  color a = color(1, 0.2, 0.4);
  color b = color(0.9, 1, 0.1);
  color c = a * b;
  color an = color(0.9, 0.2, 0.04);

  REQUIRE((c == an) == true);
}

TEST_CASE("Testing CANVAS CONSTRUCTOR ", "[single-file][canvas]") {
  canvas a = canvas(10, 20);

  REQUIRE(a.width() == 10);
  REQUIRE(a.height() == 20);
  REQUIRE((a.pixel_at(10, 10) == color(0, 0, 0)) == true);
  REQUIRE((a.pixel_at(1, 10) == color(0, 0, 0)) == true);
  REQUIRE((a.pixel_at(9, 19) == color(0, 0, 0)) == true);
}

TEST_CASE("Testing CANVAS WRITING A PIXEL", "[single-file][canvas]") {
  canvas a = canvas(10, 20);
  color red = color(1, 0, 0);
  a.write_pixel(2, 3, red);

  REQUIRE((a.pixel_at(2, 3) == red) == true);
}

TEST_CASE("Testing CANVAS to PPM header", "[single-file][ppm][canvas]") {
  canvas a = canvas(5, 3);
  REQUIRE(a.canvas_to_ppm("output_header.ppm") == 0);
}

TEST_CASE("Testing CANVAS to PPM data", "[single-file][ppm][canvas]") {
  canvas a = canvas(5, 3);
  color c1 = color(1.5, 0, 0);
  color c2 = color(0, 0.5, 0);
  color c3 = color(-0.5, 0, 1);

  a.write_pixel(0, 0, c1);
  a.write_pixel(2, 1, c2);
  a.write_pixel(4, 2, c3);
  REQUIRE(a.canvas_to_ppm("output_data.ppm") == 0);
}

TEST_CASE("Testing CANVAS to PPM data[line length]",
          "[single-file][ppm][canvas]") {
  // line length of ppm file should not be greater than 70 chars
  canvas a = canvas(10, 2);
  color c = color(1, 0.8, 0.6);

  for (int i = 0; i < a.width(); i++) {
    for (int j = 0; j < a.height(); j++) {
      a.write_pixel(i, j, c);
    }

    REQUIRE(a.canvas_to_ppm("output_data_test_line.ppm") == 0);
  }
}

TEST_CASE("REFLECTING A VECTOR APPROACHING AT 45",
          "[single-file][vec][reflect]") {
  vec v(1, -1, 0);
  vec n(0, 1, 0);
  vec result = v.reflect(n);

  REQUIRE((result == vec(1, 1, 0)) == true);
}
TEST_CASE("REFLECTING A VECTOR OFF A SLANTED SURFACE",
          "[single-file][vec][reflect]") {
  vec v(0, -1, 0);
  float f = sqrt(2) / 2;
  vec n(f, f, 0);
  vec result = v.reflect(n);

  REQUIRE((result == vec(1, 0, 0)) == true);
}

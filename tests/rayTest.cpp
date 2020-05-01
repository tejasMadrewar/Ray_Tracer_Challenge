#include "../src/ray.h"
#include "../src/transform.h"
#include "catch2/catch.hpp"

TEST_CASE("RAY CONSTRUCTOR and accesing values", "[single-file][ray]") {
  point origin(1, 2, 3);
  vec direction(4, 5, 6);
  ray r(origin, direction);
  REQUIRE((r.direction == direction) == true);
}

TEST_CASE("Computing point from a distance", "[single-file][ray]") {
  ray r(point(2, 3, 4), vec(1, 0, 0));
  REQUIRE((r.position(0) == point(2, 3, 4)) == true);
  REQUIRE((r.position(1) == point(3, 3, 4)) == true);
  REQUIRE((r.position(-1) == point(1, 3, 4)) == true);
  REQUIRE((r.position(2.5) == point(4.5, 3, 4)) == true);
}

TEST_CASE("Translating a ray", "[single-file][ray]") {
  ray r(point(1, 2, 3), vec(0, 1, 0));
  transform t;
  mat m = t.translate(3, 4, 5);

  ray result = m * r;
  REQUIRE((result.origin == point(4, 6, 8)) == true);
  REQUIRE((result.direction == vec(0, 1, 0)) == true);
}

TEST_CASE("Scaling a ray", "[single-file][ray]") {
  ray r(point(1, 2, 3), vec(0, 1, 0));
  transform t;
  mat m = t.scale(2, 3, 4);

  ray result = m * r;
  REQUIRE((result.origin == point(2, 6, 12)) == true);
  REQUIRE((result.direction == vec(0, 3, 0)) == true);
}

#include "../src/plane.h"

#include "catch2/catch.hpp"
#include <vector>

TEST_CASE("THE NORMAL OF PLANE IS CONSTANT EVERYWHERE",
          "[single-file][plane]") {
  plane p;
  vec n1, n2, n3, n(0, 1, 0);
  point p1(0, 0, 0);
  point p2(10, 0, -10);
  point p3(-5, 0, 150);

  n1 = p.localNormalAt(p1);
  n2 = p.localNormalAt(p2);
  n3 = p.localNormalAt(p3);

  REQUIRE((n1 == n) == true);
  REQUIRE((n2 == n) == true);
  REQUIRE((n3 == n) == true);
}

TEST_CASE("INTERSECT WITH A RAY PARALLEL TO THE PLANE",
          "[single-file][plane]") {
  plane p;
  ray r(point(0, 10, 0), vec(0, 0, 1));
  std::vector<intersection> xs = p.local_intersect(r);

  REQUIRE((xs.size() == 0) == true);
}

TEST_CASE("INTERSECT WITH A COPLANER RAY", "[single-file][plane]") {
  plane p;
  ray r(point(0, 0, 0), vec(0, 0, 1));
  std::vector<intersection> xs = p.local_intersect(r);

  REQUIRE((xs.size() == 0) == true);
}

TEST_CASE("A RAY INTERSECTING A PLANE FROM ABOVE", "[single-file][plane]") {
  plane p;
  ray r(point(0, 1, 0), vec(0, -1, 0));
  std::vector<intersection> xs = p.local_intersect(r);

  REQUIRE((xs.size() == 1) == true);
  REQUIRE((xs[0].intersected == 1) == true);
  REQUIRE((xs[0].obj == &p) == true);
}

TEST_CASE("A RAY INTERSECTING A PLANE FROM BELOW", "[single-file][plane]") {
  plane p;
  ray r(point(0, -1, 0), vec(0, 1, 0));
  std::vector<intersection> xs = p.local_intersect(r);

  REQUIRE((xs.size() == 1) == true);
  REQUIRE((xs[0].intersected == 1) == true);
  REQUIRE((xs[0].obj == &p) == true);
}

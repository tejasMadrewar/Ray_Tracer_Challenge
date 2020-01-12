#include "../src/sphere.h"
#include "../src/intersection.h"
#include "../src/ray.h"
#include "../src/transform.h"

#include "catch2/catch.hpp"
#include <vector>

TEST_CASE("SPHERE CONSTRUCTOR and accesing values,id",
          "[single-file][sphere]") {

  sphere a, b, c, d;
  REQUIRE(a.getID() == 0);
  REQUIRE(b.getID() == 1);
  REQUIRE(c.getID() == 2);
  REQUIRE(d.getID() == 3);
}

TEST_CASE("A RAY INTERSECT A SPHERE AT TWO POINT", "[single-file][sphere]") {

  sphere s;
  ray r(point(0, 0, -5), vec(0, 0, 1));
  std::vector<intersection> xs = s.intersect(r);

  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].intersected == 4);
  REQUIRE(xs[1].intersected == 6);
}

TEST_CASE("A RAY INTERSECT A SPHERE AT TANGENT", "[single-file][sphere]") {

  sphere s;
  ray r(point(0, 1, -5), vec(0, 0, 1));
  std::vector<intersection> xs = s.intersect(r);

  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].intersected == 5);
  REQUIRE(xs[1].intersected == 5);
}

TEST_CASE("RAY MISSES A SPHERE", "[single-file][sphere]") {

  sphere s;
  ray r(point(0, 2, -5), vec(0, 0, 1));
  std::vector<intersection> xs = s.intersect(r);

  REQUIRE(xs.size() == 0);
}

TEST_CASE("A RAY ORIGINATES INSIDE A SPHERE", "[single-file][sphere]") {

  sphere s;
  ray r(point(0, 0, 0), vec(0, 0, 1));
  std::vector<intersection> xs = s.intersect(r);

  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].intersected == -1);
  REQUIRE(xs[1].intersected == 1);
}

TEST_CASE("A SPHERE IS BEHIND A RAY", "[single-file][sphere]") {

  sphere s;
  ray r(point(0, 0, 5), vec(0, 0, 1));
  std::vector<intersection> xs = s.intersect(r);

  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].intersected == -6);
  REQUIRE(xs[1].intersected == -4);
}

TEST_CASE("INTERSECT SETS THE OBJECT ON THE INTERSECTION",
          "[single-file][sphere]") {

  sphere s;
  ray r(point(0, 0, -5), vec(0, 0, 1));
  std::vector<intersection> xs = s.intersect(r);

  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].obj == &s);
  REQUIRE(xs[1].obj == &s);
}

TEST_CASE("A SPHERE DEFAULT TRANSFORM", "[single-file][sphere]") {
  sphere s;
  REQUIRE((s.getTransform() == mat::Identity(4)) == true);
}

TEST_CASE("CHANGING A SPHERE'S TRANSFORMATION", "[single-file][sphere]") {
  sphere s;
  transform t;
  s.setTransform(t.translate(2, 3, 4));
  REQUIRE((s.getTransform() == t.translate(2, 3, 4)) == true);
}

TEST_CASE("INTERSECTING A SCALED SPHERE WITH A RAY",
          "[single-file][sphere][ray]") {
  sphere s;
  ray r(point(0, 0, -5), vec(0, 0, 1));
  transform t;
  std::vector<intersection> xs;

  s.setTransform(t.scale(2, 2, 2));

  xs = s.intersect(r);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs.at(0).intersected == 3);
  REQUIRE(xs.at(1).intersected == 7);
}

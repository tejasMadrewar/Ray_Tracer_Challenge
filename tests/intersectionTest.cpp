#include "../src/intersection.h"
#include "../src/sphere.h"
#include "../src/transform.h"
#include "./catch2/catch.hpp"
#include <vector>

TEST_CASE("INTERSECTION ENCAPSUALTES INTERSECTIONS AND OBJECT",
          "[single-file][intersections]") {

  sphere s;
  intersection i(3.5, &s);

  REQUIRE(i.intersected == 3.5);
  REQUIRE(i.obj == &s);
}

TEST_CASE("THE HIT, WHEN ALL INTERSECTIONS HAVE POSITIVE T",
          "[single-file][intersections]") {

  sphere s;
  intersection i1(1, &s);
  intersection i2(2, &s);
  intersection i;

  std::vector<intersection> xs;
  xs.push_back(i1);
  xs.push_back(i2);

  i = hit(xs);

  REQUIRE((i == i1) == true);
}

TEST_CASE("THE HIT, WHEN SOME INTERSECTIONS HAVE NAGATIVE T",
          "[single-file][intersections]") {

  sphere s;
  intersection i1(-1, &s);
  intersection i2(1, &s);
  intersection i;

  std::vector<intersection> xs;
  xs.push_back(i1);
  xs.push_back(i2);

  i = hit(xs);
  //  std::cout << i.intersected << "\n";
  //  std::cout << i.obj << "\n";

  REQUIRE((i == i2) == true);
}

TEST_CASE("THE HIT, WHEN ALL INTERSECTIONS HAVE NAGATIVE T",
          "[single-file][intersections]") {

  sphere s;
  intersection i1(-2, &s);
  intersection i2(-1, &s);
  intersection i;
  intersection allNegative(0, nullptr);

  std::vector<intersection> xs;
  xs.push_back(i1);
  xs.push_back(i2);

  i = hit(xs);

  REQUIRE((i == allNegative) == true);
}

TEST_CASE("THE HIT IS ALWAYS THE LOWEST NON NEGATIVE INTERSECTION",
          "[single-file][intersections]") {

  sphere s;
  intersection i1(5, &s);
  intersection i2(7, &s);
  intersection i3(-3, &s);
  intersection i4(2, &s);

  intersection i;
  intersection allNegative(0, nullptr);

  std::vector<intersection> xs;
  xs.push_back(i1);
  xs.push_back(i2);
  xs.push_back(i3);
  xs.push_back(i4);

  i = hit(xs);

  REQUIRE((i == i4) == true);
}

TEST_CASE("PRECOMPUTING THE STATE OF AN INTERSECTION",
          "[single-file][intersections]") {
  sphere s;
  intersection i(4, &s);
  ray r(point(0, 0, -5), vec(0, 0, 1));
  preComputed pre;
  pre = prepareComputation(i, r);

  REQUIRE((pre.eyev == vec(0, 0, -1)) == true);
  REQUIRE((pre.objptr == &s) == true);
  REQUIRE((pre.position == point(0, 0, -1)) == true);
  REQUIRE((pre.normalv == vec(0, 0, -1)) == true);
}

TEST_CASE("THE HIT, WHEN AN INTERSECTION OCCURS ON THE OUTSIDE",
          "[single-file][intersections]") {
  sphere s;
  intersection i(4, &s);
  ray r(point(0, 0, -5), vec(0, 0, 1));
  preComputed pre;
  pre = prepareComputation(i, r);

  REQUIRE((pre.inside == false) == true);
}

TEST_CASE("THE HIT, WHEN AN INTERSECTION OCCURS ON THE INSIDE",
          "[single-file][intersections]") {
  sphere s;
  intersection i(1, &s);
  ray r(point(0, 0, 0), vec(0, 0, 1));
  preComputed pre;
  pre = prepareComputation(i, r);

  REQUIRE((pre.position == point(0, 0, 1)) == true);
  REQUIRE((pre.eyev == vec(0, 0, -1)) == true);
  REQUIRE((pre.inside == true) == true);
  REQUIRE((pre.normalv == vec(0, 0, -1)) == true);
}

TEST_CASE("THE HIT SHOULD OFFSET THE POINT", "[single-file][intersections]") {
  ray r(point(0, 0, -5), vec(0, 0, 1));
  sphere s;
  transform t;
  s.setTransform(t.translate(0, 0, 1));
  intersection i(5, &s);
  preComputed pre;
  pre = prepareComputation(i, r);
  REQUIRE((pre.overPoint.t[2] < (-0.0001 / 2)) == true);
  REQUIRE((pre.position.t[2] > pre.overPoint.t[2]) == true);
}

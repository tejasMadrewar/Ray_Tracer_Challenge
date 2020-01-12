#include "../src/intersection.h"
#include "../src/sphere.h"
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

#include "../src/intersection.h"
#include "../src/plane.h"
#include "../src/sphere.h"
#include "../src/transform.h"
#include "./catch2/catch.hpp"
#include <memory>
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

TEST_CASE("Precomputing the reflective vector",
          "[single-file][intersections]") {

  std::shared_ptr<shape> s(new plane);
  ray r(point(0, 1, -1), vec(0, -sqrt(2) / 2, sqrt(2) / 2));
  intersection i(sqrt(2), s);
  preComputed p;
  p = prepareComputation(i, r);

  REQUIRE((p.reflectv == vec(0, sqrt(2) / 2, sqrt(2) / 2)) == true);
}

TEST_CASE("Finding n1 and n2 at various intersections",
          "[single-file][intersections]") {

  // auto a = sphere::glassSphere();

  auto a = std::shared_ptr<shape>(new sphere());
  auto b = std::shared_ptr<shape>(new sphere());
  auto c = std::shared_ptr<shape>(new sphere());
  auto t = transform();

  a->setTransform(t.scale(2, 2, 2));
  a->getMaterial().refractiveIndex = 1.5;
  a->getMaterial().transparency = 1.0;

  b->setTransform(t.translate(0, 0, -0.25));
  b->getMaterial().refractiveIndex = 2.0;
  b->getMaterial().transparency = 1.0;

  c->setTransform(t.translate(0, 0, 0.25));
  c->getMaterial().refractiveIndex = 2.5;
  c->getMaterial().transparency = 1.0;

  auto r = ray({0, 0, -4}, {0, 0, 1});

  // find intersection

  std::vector<intersection> xs = {
      {2, a}, {2.75, b}, {3.25, c}, {4.75, b}, {5.25, c}, {6, a},
  };

  std::vector<std::vector<float>> result = {
      {1.0, 1.5}, {1.5, 2}, {2.0, 2.5}, {2.5, 2.5}, {2.5, 1.5}, {1.5, 1.0},
  };

  preComputed pre;
  for (int i = 0; i < result.size(); i++) {
    pre = prepareComputation(xs[i], r, xs);

#define RI_DEBUG 0
#if RI_DEBUG
    std::cout << "IDX: " << i << "      n1: " << pre.n1 << " n2: " << pre.n2
              << "\n";
    std::cout << "IDX: Answer n1: " << result[i][0] << " n2: " << result[i][1]
              << "\n\n";
#endif

    REQUIRE(pre.n1 == result[i][0]);
    REQUIRE(pre.n2 == result[i][1]);
  }
}

TEST_CASE("THE UNDER POINT IS OFFSET BELOW THE SURFACE",
          "[single-file][intersections]") {

  ray r(point(0, 0, -5), vec(0, 0, 1));
  sphere s = sphere::glassSphere();
  transform t;
  s.setTransform(t.translate(0, 0, 1));
  intersection i(5, &s);
  preComputed pre;
  pre = prepareComputation(i, r);
  REQUIRE((pre.underPoint.t[2] > (-0.0001 / 2)) == true);
  REQUIRE((pre.position.t[2] < pre.underPoint.t[2]) == true);
}

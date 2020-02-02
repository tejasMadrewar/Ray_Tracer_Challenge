#include "../src/transformation.h"
#include "../src/transform.h"
#include "catch2/catch.hpp"

TEST_CASE("THE TRANSFORMATION MATRIX FOR THE DEFAULT ORIENTATION",
          "[single-file][transformation]") {
  point from = point(0, 0, 0);
  point to = point(0, 0, -1);
  vec up = vec(0, 1, 0);
  transformation trans;
  REQUIRE((trans.view_transform(from, to, up) == mat::Identity(4)) == true);
}

TEST_CASE("THE TRANSFORMATION MATRIX LOOKING IN POSITIVE Z DIRECTION",
          "[single-file][transformation]") {
  transform t;
  point from = point(0, 0, 0);
  point to = point(0, 0, 1);
  vec up = vec(0, 1, 0);
  transformation trans;

  mat answer(4);
  answer = t.scale(-1, 1, -1);
  REQUIRE((trans.view_transform(from, to, up) == answer) == true);
}

TEST_CASE("THE VIEW TRANSFORMATION MOVES THE WORLD",
          "[single-file][transformation]") {
  transform t;
  point from = point(0, 0, 8);
  point to = point(0, 0, 0);
  vec up = vec(0, 1, 0);
  transformation trans;

  mat answer(4);
  answer = t.translate(0, 0, -8);
  REQUIRE((trans.view_transform(from, to, up) == answer) == true);
}

TEST_CASE("AN ARBITRARY VIEW TRANSFORMATION", "[single-file][transformation]") {
  transform t;
  point from = point(1, 3, 2);
  point to = point(4, -2, 8);
  vec up = vec(1, 1, 0);
  transformation trans;

  mat answer(4);
  std::vector<float> temp(16);
  temp = {-0.50709, 0.50709,  0.67612,  -2.36643, 0.76772,  0.60609,
          0.12122,  -2.82843, -0.35857, 0.59761,  -0.71714, 0.0000,
          0.0000,   0.0000,   0.0000,   1};
  answer.from_vec(temp);

  REQUIRE((trans.view_transform(from, to, up) == answer) == true);
}

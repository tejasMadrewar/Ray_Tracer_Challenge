#include "../src/light.h"
#include "catch2/catch.hpp"

TEST_CASE("A POINT LIGHT HAS A POSITION AND INTENSITY",
          "[single-file][light]") {
  pointLight a;
  a.intensity = color(1, 1, 1);
  a.position = point(0, 0, 0);

  REQUIRE((a.intensity == color(1, 1, 1)) == true);
  REQUIRE((a.position == point(0, 0, 0)) == true);
}

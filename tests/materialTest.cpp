#include "../src/material.h"
#include "../src/light.h"
#include "../src/stripePattern.h"
#include "catch2/catch.hpp"
#include <memory>

TEST_CASE("The default material of MATERIAL", "[single-file][material]") {
  material m;

  REQUIRE(m.ambient == Approx(0.1));
  REQUIRE(m.diffuse == Approx(0.9));
  REQUIRE(m.specular == Approx(0.9));
  REQUIRE(m.shiniess == Approx(200));
  REQUIRE((m.col == color(1, 1, 1)) == true);
}

TEST_CASE("LIGHTENING WITH THE EYE BETWEEN THE LIGHT AND THE SURFACE",
          "[single-file][material]") {
  material m;
  point position(0, 0, 0);
  vec eyev, normalv;
  pointLight l;
  color result;

  eyev = vec(0, 0, -1);
  normalv = vec(0, 0, -1);

  l.position = point(0, 0, -10);
  l.intensity = color(1, 1, 1);

  result = lightening(m, l, position, eyev, normalv);

  REQUIRE((result == color(1.9, 1.9, 1.9)) == true);
}

TEST_CASE(
    "LIGHTENING WITH THE EYE BETWEEN LIGHT AND SURFACE, EYE OFFSET 45 DEGREE",
    "[single-file][material]") {
  material m;
  point position(0, 0, 0);
  vec eyev, normalv;
  pointLight l;
  color result;

  float f = sqrt(2) / 2;
  eyev = vec(0, f, f);
  normalv = vec(0, 0, -1);

  l.position = point(0, 0, -10);
  l.intensity = color(1, 1, 1);

  result = lightening(m, l, position, eyev, normalv);

  REQUIRE((result == color(1, 1, 1)) == true);
}

TEST_CASE("LIGHTENING WITH THE EYE OPPOSITE SURFACE, LIGHT OFFSET 45 DEGREE",
          "[single-file][material]") {
  material m;
  point position(0, 0, 0);
  vec eyev, normalv;
  pointLight l;
  color result;

  eyev = vec(0, 0, -1);
  normalv = vec(0, 0, -1);

  l.position = point(0, 10, -10);
  l.intensity = color(1, 1, 1);

  result = lightening(m, l, position, eyev, normalv);

  REQUIRE((result == color(0.7364, 0.7364, 0.7364)) == true);
}

TEST_CASE("LIGHTENING WITH EYE IN THE PATH OF THE REFLECTION VECTOR",
          "[single-file][material]") {
  material m;
  point position(0, 0, 0);
  vec eyev, normalv;
  pointLight l;
  color result;

  float f = sqrt(2) / 2;
  eyev = vec(0, -f, -f);
  normalv = vec(0, 0, -1);

  l.position = point(0, 10, -10);
  l.intensity = color(1, 1, 1);

  result = lightening(m, l, position, eyev, normalv);

  REQUIRE((result == color(1.6364, 1.6364, 1.6364)) == true);
}

TEST_CASE("LIGHTENING WITH THE LIGHT BEHIND THE SURFACE",
          "[single-file][material]") {
  material m;
  point position(0, 0, 0);
  vec eyev, normalv;
  pointLight l;
  color result;

  eyev = vec(0, 0, -1);
  normalv = vec(0, 0, -1);

  l.position = point(0, 0, 10);
  l.intensity = color(1, 1, 1);

  result = lightening(m, l, position, eyev, normalv);

  REQUIRE((result == color(0.1, 0.1, 0.1)) == true);
}

TEST_CASE("LIGHTENING WITH THE SURFACE IN SHADOW", "[single-file][material]") {
  material m;
  point position(0, 0, 0);
  vec eyev, normalv;
  pointLight l;
  color result;
  bool in_shadow;

  eyev = vec(0, 0, -1);
  normalv = vec(0, 0, -1);

  l.position = point(0, 0, -10);
  l.intensity = color(1, 1, 1);

  in_shadow = true;
  result = lightening(m, l, position, eyev, normalv, in_shadow);

  REQUIRE((result == color(0.1, 0.1, 0.1)) == true);
}

TEST_CASE("Lightening with a pattern applied",
          "[single-file][material][pattern]") {

  vec eyev, normalv;
  pointLight l;
  material m;
  color result1;
  color result2;
  bool in_shadow;
  std::shared_ptr<pattern> p(new stripePattern(color(1, 1, 1), color(0, 0, 0)));

  m.ambient = 1;
  m.diffuse = 0;
  m.specular = 0;

  m.setPattern(p);
  // m.setStripePattern(color(1, 1, 1), color(0, 0, 0));

  point position1(0.9, 0, 0);
  point position2(1.1, 0, 0);

  eyev = vec(0, 0, -1);
  normalv = vec(0, 0, -1);

  l.position = point(0, 0, -10);
  l.intensity = color(1, 1, 1);

  in_shadow = false;
  result1 = lightening(m, l, position1, eyev, normalv, in_shadow);
  result2 = lightening(m, l, position2, eyev, normalv, in_shadow);

  REQUIRE((result1 == color(1, 1, 1)) == true);
  REQUIRE((result2 == color(0, 0, 0)) == true);
}

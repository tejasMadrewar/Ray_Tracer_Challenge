#include "../src/camera.h"
#include "../src/transform.h"
#include "../src/transformation.h"
#include "catch2/catch.hpp"
#include <iostream>

TEST_CASE("CONSTRUCTING A CAMERA", "[single-file][camera]") {
  float PI = 3.1415927;
  int hsize = 160;
  int vsize = 120;
  float fieldOfView = PI / 2;
  camera c(hsize, vsize, fieldOfView);

  REQUIRE(c.hsize == hsize);
  REQUIRE(c.vsize == vsize);
  REQUIRE(c.fieldOfView == fieldOfView);
  REQUIRE((c.getTransform() == mat::Identity(4)) == true);
}

TEST_CASE("THE PIXEL SIZE FOR A HORIZONTAL CANVAS", "[single-file][camera]") {
  float PI = 3.1415927;
  camera c(200, 125, PI / 2);

  REQUIRE(c.pixelSize == Approx(0.01));
}

TEST_CASE("THE PIXEL SIZE FOR A VERTICAL CANVAS", "[single-file][camera]") {
  float PI = 3.1415927;
  camera c(125, 200, PI / 2);
  REQUIRE(c.pixelSize == Approx(0.01));
}

TEST_CASE("CONSTRUCTING A RAY THROUGH THE CENTER OF THE CANVAS",
          "[single-file][camera]") {
  float PI = 3.1415927;
  camera c(201, 101, PI / 2);
  ray r = c.ray_for_pixel(100, 50);

  REQUIRE((r.origin == point(0, 0, 0)) == true);
  REQUIRE((r.direction == vec(0, 0, -1)) == true);
}

TEST_CASE("CONSTRUCTING A RAY THROUGH A CORNER OF THE CANVAS",
          "[single-file][camera]") {
  float PI = 3.1415927;
  camera c(201, 101, PI / 2);
  ray r = c.ray_for_pixel(0, 0);

  REQUIRE((r.origin == point(0, 0, 0)) == true);
  REQUIRE((r.direction == vec(0.66519, 0.33259, -0.66851)) == true);
}

TEST_CASE("CONSTRUCTING A RAY WHEN THE CAMERA IS TRANSFORMED",
          "[single-file][camera]") {
  float PI = 3.1415927;
  float temp = sqrt(2) / 2;
  transform t;
  vec answer = vec(temp, 0, -temp);
  mat transMat = t.rotY(PI / 4) * t.translate(0, -2, 5);
  camera c(201, 101, PI / 2);
  c.setTransform(transMat);

  ray r = c.ray_for_pixel(100, 50);

  REQUIRE((r.origin == point(0, 2, -5)) == true);

  REQUIRE((r.direction == answer) == true);
}

TEST_CASE("RENDERING A WORLD WITH A CAMERA", "[single-file][camera]") {
  float PI = 3.1415927;
  world w = world::default_world();
  transformation trans;
  camera c(11, 11, PI / 2);
  point from(0, 0, -5);
  point to(0, 0, 0);
  vec up(0, 1, 0);
  mat viewTransform = trans.view_transform(from, to, up);
  c.setTransform(viewTransform);
  canvas image;

  image = c.render(w);
  image.canvas_to_ppm("cameraTest.ppm");

  REQUIRE((image.pixel_at(5, 5) == color(0.38066, 0.47583, 0.2855)) == true);
}

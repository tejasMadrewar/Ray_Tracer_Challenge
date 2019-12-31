#include "../src/mat.h"
#include "../src/canvas.h"
#include "../src/color.h"
#include "../src/point.h"
#include "../src/tuple.h"
#include "../src/vec.h"
#include "catch2/catch.hpp"

TEST_CASE("Testing MATRIX CONSTRUCTOR", "[single-file][matrix]") {
  mat m = mat(4, 4);

  m.at(0, 0) = 1;
  m.at(0, 1) = 2;
  m.at(0, 2) = 3;
  m.at(0, 3) = 4;

  m.at(1, 0) = 5.5;
  m.at(1, 1) = 6.5;
  m.at(1, 2) = 7.5;
  m.at(1, 3) = 8.5;

  m.at(2, 0) = 9;
  m.at(2, 1) = 10;
  m.at(2, 2) = 11;
  m.at(2, 3) = 12;

  m.at(3, 0) = 13.5;
  m.at(3, 1) = 14.5;
  m.at(3, 2) = 15.5;
  m.at(3, 3) = 16.5;

  REQUIRE(m.at(0, 0) == Approx(1));
  REQUIRE(m.at(0, 3) == Approx(4));
  REQUIRE(m.at(1, 0) == Approx(5.5));
  REQUIRE(m.at(1, 2) == Approx(7.5));
  REQUIRE(m.at(2, 2) == Approx(11));
  REQUIRE(m.at(3, 0) == Approx(13.5));
  REQUIRE(m.at(3, 2) == Approx(15.5));
}

TEST_CASE("Testing MATRIX COPY CONSTRUCTOR", "[single-file][matrix]") {
  mat m = mat(4, 4);

  m.at(0, 0) = 1;
  m.at(0, 1) = 2;
  m.at(0, 2) = 3;
  m.at(0, 3) = 4;

  m.at(1, 0) = 5.5;
  m.at(1, 1) = 6.5;
  m.at(1, 2) = 7.5;
  m.at(1, 3) = 8.5;

  m.at(2, 0) = 9;
  m.at(2, 1) = 10;
  m.at(2, 2) = 11;
  m.at(2, 3) = 12;

  m.at(3, 0) = 13.5;
  m.at(3, 1) = 14.5;
  m.at(3, 2) = 15.5;
  m.at(3, 3) = 16.5;

  mat n = m;
  n.at(3, 3) = 17.5;

  REQUIRE(n.at(0, 0) == Approx(1));
  REQUIRE(n.at(0, 3) == Approx(4));
  REQUIRE(n.at(1, 0) == Approx(5.5));
  REQUIRE(n.at(1, 2) == Approx(7.5));
  REQUIRE(n.at(2, 2) == Approx(11));
  REQUIRE(n.at(3, 0) == Approx(13.5));
  REQUIRE(n.at(3, 2) == Approx(15.5));

  REQUIRE(n.at(3, 3) == Approx(17.5));
  REQUIRE(m.at(3, 3) == Approx(16.5));
}

TEST_CASE("Testing MATRIX 2X2", "[single-file][matrix]") {
  mat m = mat(2, 2);

  m.at(0, 0) = -3;
  m.at(0, 1) = 5;
  m.at(1, 0) = 1;
  m.at(1, 1) = -2;

  REQUIRE(m.at(0, 0) == Approx(-3));
  REQUIRE(m.at(0, 1) == Approx(5));
  REQUIRE(m.at(1, 0) == Approx(1));
  REQUIRE(m.at(1, 1) == Approx(-2));
}

TEST_CASE("Testing MATRIX 3X3", "[single-file][matrix]") {
  mat m = mat(3, 3);

  m.at(0, 0) = -3;
  m.at(0, 1) = 5;
  m.at(0, 2) = 0;

  m.at(1, 0) = 1;
  m.at(1, 1) = -2;
  m.at(1, 2) = -7;

  m.at(2, 0) = 0;
  m.at(2, 1) = 1;
  m.at(2, 2) = 1;

  REQUIRE(m.at(0, 0) == Approx(-3));
  REQUIRE(m.at(1, 1) == Approx(-2));
  REQUIRE(m.at(2, 2) == Approx(1));
}

TEST_CASE("Testing MATRIX COMPARISION", "[single-file][matrix]") {
  mat a = mat(4, 4);
  mat b = mat(4, 4);
  mat c = mat(4, 4);

  a.at(0, 0) = 1;
  a.at(0, 1) = 2;
  a.at(0, 2) = 3;
  a.at(0, 3) = 4;

  a.at(1, 0) = 5;
  a.at(1, 1) = 6;
  a.at(1, 2) = 7;
  a.at(1, 3) = 8;

  a.at(2, 0) = 9;
  a.at(2, 1) = 8;
  a.at(2, 2) = 7;
  a.at(2, 3) = 6;

  a.at(3, 0) = 5;
  a.at(3, 1) = 4;
  a.at(3, 2) = 3;
  a.at(3, 3) = 2;

  b.at(0, 0) = 1;
  b.at(0, 1) = 2;
  b.at(0, 2) = 3;
  b.at(0, 3) = 4;

  b.at(1, 0) = 5;
  b.at(1, 1) = 6;
  b.at(1, 2) = 7;
  b.at(1, 3) = 8;

  b.at(2, 0) = 9;
  b.at(2, 1) = 8;
  b.at(2, 2) = 7;
  b.at(2, 3) = 6;

  b.at(3, 0) = 5;
  b.at(3, 1) = 4;
  b.at(3, 2) = 3;
  b.at(3, 3) = 2;

  c.at(0, 0) = 2;
  c.at(0, 1) = 3;
  c.at(0, 2) = 4;
  c.at(0, 3) = 5;
  c.at(1, 0) = 6;
  c.at(1, 1) = 7;
  c.at(1, 2) = 8;
  c.at(1, 3) = 9;
  c.at(2, 0) = 8;
  c.at(2, 1) = 7;
  c.at(2, 2) = 6;
  c.at(2, 3) = 5;
  c.at(3, 0) = 4;
  c.at(3, 1) = 3;
  c.at(3, 2) = 2;
  c.at(3, 3) = 1;

  REQUIRE((a == b) == true);
  REQUIRE((a != c) == true);
}

TEST_CASE("Testing MATRIX 2X2 vector CONSTRUCTOR", "[single-file][matrix]") {
  mat m = mat(2, 2);

  std::vector<float> v(4);
  v = {-3, 5, 1, -2};
  mat n = mat(2, 2);
  n.from_vec(v);

  m.at(0, 0) = -3;
  m.at(0, 1) = 5;
  m.at(1, 0) = 1;
  m.at(1, 1) = -2;

  REQUIRE((m == n) == true);

  // std::cout << "Vector m\n";
  // m.print();
  // std::cout << "Vector n\n";
  // n.print();
}

TEST_CASE("Testing MATRIX MULTIPLICATION with MATRIX",
          "[single-file][matrix]") {
  mat m = mat(4, 4);
  mat n = mat(4, 4);
  mat ans = mat(4, 4);

  std::vector<float> v(16);
  v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
  m.from_vec(v);

  v.clear();
  v = {-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8};
  n.from_vec(v);

  v.clear();
  v = {20, 22, 50, 48, 44, 54, 114, 108, 40, 58, 110, 102, 16, 26, 46, 42};
  ans.from_vec(v);

  mat result = m * n;

  //  std::cout << "m = \n";
  //  m.print();
  //  std::cout << "n = \n";
  //  n.print();
  //  std::cout << "m*n = \n";
  //  result.print();
  //  std::cout << "ans = \n";
  //  ans.print();

  REQUIRE((ans == result) == true);
}

TEST_CASE("Testing MATRIX MULTIPLICATION with TUPLE",
          "[single-file][matrix][tuple]") {
  mat m = mat(4, 4);
  tuple t, ans;
  t.t[0] = 1;
  t.t[1] = 2;
  t.t[2] = 3;
  t.t[3] = 1;

  ans.t[0] = 18;
  ans.t[1] = 24;
  ans.t[2] = 33;
  ans.t[3] = 1;

  std::vector<float> v(16);
  v = {1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1};
  m.from_vec(v);

  tuple result = m * t;

  REQUIRE((ans == result) == true);
}

TEST_CASE("Testing MATRIX MULTIPLICATION with Identity MATRIX",
          "[single-file][matrix][tuple]") {
  mat m = mat(4, 4);
  tuple tup;

  tup.t[0] = 1;
  tup.t[1] = 2;
  tup.t[2] = 3;
  tup.t[3] = 4;

  std::vector<float> v(16);
  v = {0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32};
  m.from_vec(v);

  REQUIRE(((m * m.Identity(4)) == m) == true);
  REQUIRE(((m.Identity(4) * tup) == tup) == true);
}

TEST_CASE("Testing MATRIX transpose ", "[single-file][matrix]") {
  mat m = mat(4, 4);
  mat ans = mat(4, 4);
  tuple tup;

  std::vector<float> v(16);
  v = {0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8};
  m.from_vec(v);

  v.clear();
  v = {0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8};

  ans.from_vec(v);

  REQUIRE((ans == m.transpose()) == true);
  REQUIRE((m.Identity(4) == m.Identity(4).transpose()) == true);
}

TEST_CASE("Testing 2X2 MATRIX Determinant", "[single-file][matrix]") {
  mat m = mat(2);

  std::vector<float> v(4);
  v = {1, 5, -3, 2};
  m.from_vec(v);

  REQUIRE((m.det() == 17) == true);
}

TEST_CASE("Testing MATRIX Submatrix", "[single-file][matrix]") {
  mat m3 = mat(3);
  mat ans3 = mat(2);

  mat m4 = mat(4);
  mat ans4 = mat(3);

  std::vector<float> v(9);
  v = {1, 5, 0, -3, 2, 7, 0, 6, -3};
  m3.from_vec(v);

  v.clear();
  v = {-3, 2, 0, 6};
  ans3.from_vec(v);

  v.clear();
  v = {-6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1};
  m4.from_vec(v);

  v.clear();
  v = {-6, 1, 6, -8, 8, 6, -7, -1, 1};
  ans4.from_vec(v);

  REQUIRE((m3.subMat(0, 2) == ans3) == true);
  REQUIRE((m4.subMat(2, 1) == ans4) == true);
}

TEST_CASE("Testing MATRIX minors of 3X3", "[single-file][matrix]") {
  mat m3 = mat(3);
  mat sub = mat(2);
  mat ans3 = mat(2);
  float Determinant;

  std::vector<float> v(9);
  v = {3, 5, 0, 2, -1, -7, 6, -1, 5};
  m3.from_vec(v);

  sub = m3.subMat(1, 0);
  Determinant = sub.det();

  REQUIRE(m3.minor(1, 0) == 25);
  REQUIRE(Determinant == 25);
}

TEST_CASE("Testing MATRIX cofactor of 3X3", "[single-file][matrix]") {
  mat m3 = mat(3);
  mat sub = mat(2);
  mat ans3 = mat(2);
  float Determinant;

  std::vector<float> v(9);
  v = {3, 5, 0, 2, -1, -7, 6, -1, 5};
  m3.from_vec(v);

  sub = m3.subMat(1, 0);
  Determinant = sub.det();

  REQUIRE(m3.minor(0, 0) == -12);
  REQUIRE(m3.cofactor(0, 0) == -12);

  REQUIRE(m3.minor(1, 0) == 25);
  REQUIRE(m3.cofactor(1, 0) == -25);
}

TEST_CASE("Testing MATRIX Determinant of 3X3", "[single-file][matrix]") {
  mat m3(3);
  std::vector<float> v(9);
  v = {1, 2, 6, -5, 8, -4, 2, 6, 4};
  m3.from_vec(v);

  REQUIRE(m3.cofactor(0, 0) == 56);
  REQUIRE(m3.cofactor(0, 1) == 12);
  REQUIRE(m3.cofactor(0, 2) == -46);
  REQUIRE(m3.det() == -196);
}

TEST_CASE("Testing MATRIX Determinant of 4X4", "[single-file][matrix]") {
  mat m3(4);
  std::vector<float> v(16);
  v = {-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9};
  m3.from_vec(v);

  REQUIRE(m3.cofactor(0, 0) == 690);
  REQUIRE(m3.cofactor(0, 1) == 447);
  REQUIRE(m3.cofactor(0, 2) == 210);
  REQUIRE(m3.cofactor(0, 3) == 51);
  REQUIRE(m3.det() == -4071);
}

TEST_CASE("Testing MATRIX invertable of 4X4", "[single-file][matrix]") {
  mat m4(4);
  mat m5(4);

  std::vector<float> v(16);
  v = {6, 4, 4, 4, 5, 5, 7, 6, 4, -9, 3, -7, 9, 1, 7, -6};
  m4.from_vec(v);

  v = {-4, 2, -2, -3, 9, 6, 2, 6, 0, -5, 1, -5, 0, 0, 0, 0};
  m5.from_vec(v);

  REQUIRE(m4.det() == -2120);
  REQUIRE(m4.invertable() == true);

  REQUIRE(m5.det() == 0);
  REQUIRE(m5.invertable() == false);
}

TEST_CASE("Testing MATRIX inverse of 4X4", "[single-file][matrix]") {
  mat m4(4);
  mat ans(4);
  mat result(4);

  std::vector<float> v(16);
  v = {-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4};
  m4.from_vec(v);

  v = {0.21805,  0.45113,  0.24060,  -0.04511, -0.80827, -1.45677,
       -0.44361, 0.52068,  -0.07895, -0.22368, -0.05263, 0.19737,
       -0.52256, -0.81391, -0.30075, 0.30639};
  ans.from_vec(v);

  result = m4.inverse();
  // result.print();

  REQUIRE(m4.det() == 532);

  REQUIRE(m4.cofactor(2, 3) == -160);
  REQUIRE(result.at(3, 2) == Approx((-160.0 / 532.0)));

  REQUIRE(m4.cofactor(3, 2) == 105);
  REQUIRE(result.at(2, 3) == Approx((105.0 / 532.0)));

  REQUIRE(m4.invertable() == true);
  REQUIRE((ans == result) == true);
}

TEST_CASE("Testing MATRIX inverse of 4X4 [a]", "[single-file][matrix]") {
  mat m4(4);
  mat ans(4);
  mat result(4);

  std::vector<float> v(16);
  v = {8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4};
  m4.from_vec(v);

  v = {-0.15385, -0.15385, -0.28205, -0.53846, -0.07692, 0.12308,
       0.02564,  0.03077,  0.35897,  0.35897,  0.43590,  0.92308,
       -0.69231, -0.69231, -0.76923, -1.92308};
  ans.from_vec(v);

  result = m4.inverse();
  // result.print();

  REQUIRE((ans == result) == true);
}

TEST_CASE("Testing MATRIX inverse of 4X4 [b]", "[single-file][matrix]") {
  mat m4(4);
  mat ans(4);
  mat result(4);

  std::vector<float> v(16);
  v = {9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2};
  m4.from_vec(v);

  v = {-0.04074, -0.07778, 0.14444,  -0.22222, -0.07778, 0.03333,
       0.36667,  -0.33333, -0.02901, -0.14630, -0.10926, 0.12963,
       0.17778,  0.06667,  -0.26667, 0.33333

  };
  ans.from_vec(v);

  result = m4.inverse();
  // result.print();

  REQUIRE((ans == result) == true);
}

TEST_CASE("Testing MATRIX 4X4 multiply a product by inverse",
          "[single-file][matrix]") {
  mat a(4);
  mat b(4);
  mat c(4);
  mat result(4);

  std::vector<float> v(16);
  v = {3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1};
  a.from_vec(v);

  v = {8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5};
  b.from_vec(v);
  c = a * b;

  REQUIRE(((c * b.inverse()) == a) == true);
}

TEST_CASE("chapter 2 EXERCISE", "[single-file][matrix]") {
  mat a(4);
  mat b(4);
  mat c(4);
  mat result(4);

  std::vector<float> v(16);
  v = {3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1};
  a.from_vec(v);

  v = {8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5};
  b.from_vec(v);

  //  // invert Identity matrix
  //  std::cout << "------------invert Identity matrix ------\n";
  //  a.Identity(4).inverse().print();
  //  std::cout << "---------------------------------------\n\n";
  //
  //  std::cout << "-----------multiply matrix by inverse----\n";
  //  (a * a.inverse()).print();
  //  if ((a * a.inverse()) == a.Identity(4))
  //    std::cout << "Its Identity matrix\n";
  //  std::cout << "---------------------------------------\n\n";
  //
  //  std::cout << "------inverse of transpose of matrix-----\n";
  //  std::cout << "-----a\n";
  //  a.print();
  //  std::cout << "-----inverse of transpose of matrix\n";
  //  a.transpose().inverse().print();
  //  std::cout << "-----transpose of inverse of matrix\n";
  //  a.inverse().transpose().print();
  //  if (a.transpose().inverse() == a.inverse().transpose())
  //    std::cout << "They are EQUAL\n";
  //  else
  //    std::cout << "They are NOT EQUAL\n";
  //
  //  std::cout << "---------------------------------------\n\n";
}

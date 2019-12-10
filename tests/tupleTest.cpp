#include "catch2/catch.hpp"
#include "../src/tuple.h"
#include "../src/point.h"
#include "../src/vec.h"

TEST_CASE( "tuple constructor and accesing values", "[single-file]" ) {
	tuple a = tuple();
	tuple b = tuple(1,2,3,0);
	tuple c = tuple(1,2,3,1);
	REQUIRE(a.getX() == 0);
	REQUIRE(a.getY() == 0);
	REQUIRE(a.getZ() == 0);
	REQUIRE(a.getW() == 0);

	REQUIRE(b.getX() == 1);
	REQUIRE(b.getY() == 2);
	REQUIRE(b.getZ() == 3);
	REQUIRE(b.getW() == 0);

	// point
	REQUIRE(b.isPoint() == true);
	REQUIRE(b.isVector() == false);
	// vector
	REQUIRE(c.isPoint() == false);
	REQUIRE(c.isVector() == true);

}

TEST_CASE( "Testing POINT constructor", "[single-file]" ) {
	point a = point();
	point b = point(1,2,3);
	point c = point(1,2,3);
	REQUIRE(a.getX() == 0);
	REQUIRE(a.getY() == 0);
	REQUIRE(a.getZ() == 0);
	REQUIRE(a.getW() == 0);

	REQUIRE(b.getX() == 1);
	REQUIRE(b.getY() == 2);
	REQUIRE(b.getZ() == 3);
	REQUIRE(b.getW() == 0);

	// point
	REQUIRE(b.isPoint() == true);
	REQUIRE(b.isVector() == false);
	REQUIRE(c.isPoint() == true);
	REQUIRE(c.isVector() == false);

}

TEST_CASE( "Testing VECTOR constructor", "[single-file]" ) {
	vec a = vec();
	vec b = vec(1,2,3);
	vec c = vec(1,2,3);
	REQUIRE(a.getX() == 0);
	REQUIRE(a.getY() == 0);
	REQUIRE(a.getZ() == 0);
	REQUIRE(a.getW() == 1);

	REQUIRE(b.getX() == 1);
	REQUIRE(b.getY() == 2);
	REQUIRE(b.getZ() == 3);
	REQUIRE(b.getW() == 1);

	// point
	REQUIRE(b.isPoint() == false);
	REQUIRE(b.isVector() == true);
	REQUIRE(c.isPoint() == false);
	REQUIRE(c.isVector() == true);

}

TEST_CASE( "Testing comparision of tuple", "[single-file]" ) {
	tuple a = tuple(4.3, -4.2, 3.1, 1.0);
	tuple b = tuple(4.3, -4.2, 3.1, 1.0);
	tuple c = tuple(4.3, -4.1, 3.1, 1.0);
	REQUIRE((a == b) == true);
	REQUIRE((a == c) == false);

}

TEST_CASE( "Testing comparision of tuple with vector", "[single-file]" ) {
	tuple a = tuple(4.3, -4.2, 3.1, 1.0);
	vec b = vec(4.3, -4.2, 3.1);
	vec d = vec(4.3, -4.1, 3.1);
	vec e = vec(4.3, -4.1, 3.1);

	// tuple vector
	REQUIRE((a == b) == true);
	REQUIRE((b == a) == true);


	// vector vector
	REQUIRE((b == d) == false);
	REQUIRE((d == b) == false);
	REQUIRE((e == d) == true);
	REQUIRE((d == e) == true);

}

TEST_CASE( "Testing comparision of tuple with point", "[single-file]" ) {
	tuple a = tuple(4.3, -4.2, 3.1, 0.0);
	point b = point(4.3, -4.2, 3.1);
	point d = point(4.3, -4.1, 3.1);
	point e = point(4.3, -4.1, 3.1);

	// tuple point
	REQUIRE((a == b) == true);
	REQUIRE((b == a) == true);


	// point point
	REQUIRE((b == d) == false);
	REQUIRE((d == b) == false);
	REQUIRE((e == d) == true);
	REQUIRE((d == e) == true);

}

TEST_CASE( "Testing comparision of vector with point", "[single-file]" ) {
	vec a = vec(4.3, -4.2, 3.1);
	point b = point(4.3, -4.2, 3.1);

	// vec point
	REQUIRE((a == b) == false);
	REQUIRE((b == a) == false);

}

TEST_CASE( "Testing ADDITION of tuple ", "[single-file]" ) {
	tuple a = tuple(3, -2, 5, 1);
	tuple b = tuple(-2, 3, 1, 0);
	tuple c = tuple(1, 1, 6, 1);
	tuple d = tuple(1, 1, 7, 1);

	// addition test
	REQUIRE(((a + b) == c) == true);
	REQUIRE(((a + b) == d) == false);

}

TEST_CASE( "Testing SUBTRACTION of tuple ", "[single-file]" ) {
	tuple a = tuple(3, 2, 1, 1);
	tuple b = tuple(5, 3, 7, 1);
	tuple c = tuple(-2, -1, -6, 0);
	tuple d = tuple(1, 1, 7, 1);

	// SUBTRACTION test
	REQUIRE(((a - b) == c) == true);
	REQUIRE(((a - b) == d) == false);

}

TEST_CASE( "Testing SUBTRACTION of point ", "[single-file]" ) {
	point a = point(3, 2, 1);
	point b = point(5, 6, 7);
	vec c = vec(-2, -4, -6);
	vec d = vec(2, -4, -6);

	// SUBTRACTION test
	REQUIRE(((a - b) == c) == true);
	REQUIRE(((a - b) == d) == false);

}

TEST_CASE( "Testing SUBTRACTION of point - vector ", "[single-file]" ) {
	point a = point(3, 2, 1);
	vec b = vec(5, 6, 7);
	point c = point(-2, -4, -6);
	point d = point(2, -4, -6);

	// SUBTRACTION test
	REQUIRE(((a - b) == c) == true);
	REQUIRE(((a - b) == d) == false);

}

TEST_CASE( "Testing SUBTRACTION of vector - vector ", "[single-file]" ) {
	vec a = vec(3, 2, 1);
	vec b = vec(5, 6, 7);
	vec c = vec(-2, -4, -6);
	vec d = vec(2, -4, -6);

	// SUBTRACTION test
	REQUIRE(((a - b) == c) == true);
	REQUIRE(((a - b) == d) == false);

}

TEST_CASE( "Testing Negating tuple", "[single-file]" ) {
	tuple a = tuple(1, -2, 3, -4);
	tuple b = tuple(-1, 2, -3, 4);
	tuple c = tuple(-1, -2, -3, 4);

	// Negation test
	REQUIRE((-a == b) == true);
	REQUIRE((a == -b) == true);
	REQUIRE((-a == c) == false);

}

TEST_CASE( "Testing Negating vector", "[single-file]" ) {
	vec a = vec(1, -2, 3);
	vec b = vec(-1, 2, -3);
	vec c = vec(-1, -2, -3);

	// Negation test
	REQUIRE((-a == b) == true);
	REQUIRE((a == -b) == true);
	REQUIRE((-a == c) == false);

}

TEST_CASE( "Testing Scalar MULTIPLICATION  with tuple", "[single-file]" ) {
	tuple a = tuple(1, -2, 3, -4);
	tuple b = tuple(3.5, -7, 10.5, -14);
	tuple c = tuple(0.5, -1, 1.5, -2);

	// scalar multiplication test
	REQUIRE(((a * 3.5 ) == b) == true);
	REQUIRE(((a * 0.5 ) == c) == true);

}

TEST_CASE( "Testing Scalar DIVIDING  with tuple", "[single-file]" ) {
	tuple a = tuple(1, -2, 3, -4);
	tuple b = tuple(0.5, -1, 1.5, -2);

	// scalar divison test
	REQUIRE(((a / 2 ) == b) == true);

}

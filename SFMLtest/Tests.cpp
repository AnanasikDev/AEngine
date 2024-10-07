#define CATCH_CONFIG_MAIN

#include "catch_amalgamated.hpp"

#include "Vector.h"
#include "Mathf.h"
#include "Physics.h"
#include "Bounds.h"
#include <tuple>
#include "Line.h"

namespace aengine {
	TEST_CASE("Vector operations") {
		REQUIRE(Vectorf::zero.getLength() == 0);
		REQUIRE(Vectorf(3, 4).getLength() == 5);
		REQUIRE(Vectorf(-3, 4).getLength() == 5);
		
		auto a = Vectorf(4, 2);
		auto b = Vectorf(2, 4);
		auto c = Vectorf(-3, 3);
		auto d = Vectorf(-4, -2);
		auto e = Vectorf(-2, -4);
		auto f = Vectorf(3, -3);

		REQUIRE((a.dotProduct(b) > 0));
		REQUIRE((b.crossProduct(c) > 0));
		REQUIRE((c.crossProduct(b) < 0));
		REQUIRE((b.crossProduct(e) == 0));
		REQUIRE((a.crossProduct(a) == 0));
	}

	TEST_CASE("Bounds") {
		Bounds b;
		REQUIRE(b.getArea() == 0);
		b.setCenterAndSize(Vectorf::zero, Vectorf(10, 5));
		REQUIRE(b.getArea() == 50);
		auto points = b.getPoints();

		REQUIRE(points[0] == Vectorf(-5, -2.5f));
		REQUIRE(points[1] == Vectorf(5, -2.5f));
		REQUIRE(points[2] == Vectorf(5, 2.5f));
		REQUIRE(points[3] == Vectorf(-5, 2.5f));

		Bounds b1(Vectorf(0, 0), Vectorf(5, 6));
		Bounds b2(Vectorf(3, 1), Vectorf(6, 8));
		Bounds b3(Vectorf(-3, 1), Vectorf(-1, 3));
		Bounds b4(Vectorf(1, 1), Vectorf(3, 5));

		REQUIRE(Bounds::areIntersecting(b1, b2));
		REQUIRE(!Bounds::areIntersecting(b1, b3));
		REQUIRE(Bounds::areIntersecting(b1, b4));

		REQUIRE((Bounds::getIntersectionBounds(b1, b2) == Bounds(Vectorf(3, 1), Vectorf(5, 6))));
		REQUIRE((Bounds::getIntersectionBounds(b3, b4) == Bounds::empty));
		REQUIRE((Bounds::getIntersectionBounds(b1, b4) == b4));
		REQUIRE((Bounds::getIntersectionBounds(b4, b2) == Bounds::empty));
		REQUIRE((Bounds::getIntersectionBounds(Bounds(0, 385, 800, 415), Bounds(75, 380, 105, 410)) == Bounds::Bounds(75, 385, 105, 410)));

		REQUIRE((b4.getCenter() == Vectorf(2, 3)));
	}

	TEST_CASE("Line_isPointOnLine") {
		Line a(Vectorf(0, 0), Vectorf(7, 7));
		REQUIRE(Line::isPointOnLine(a, Vectorf(4, 4)));
		REQUIRE(!Line::isPointOnLine(a, Vectorf(8, 8)));
		REQUIRE(!Line::isPointOnLine(a, Vectorf(3, 4)));
		REQUIRE(!Line::isPointOnLine(a, Vectorf(-3, -3)));
		REQUIRE(!Line::isPointOnLine(a, Vectorf(-3, -10)));
		REQUIRE(Line::isPointOnLine(a, Vectorf(0, 0)));
		REQUIRE(Line::isPointOnLine(a, Vectorf(7, 7)));
	}

	TEST_CASE("Line_areIntersecting") {
		Line a(Vectorf(0, 0), Vectorf(5, 4));
		Line b(Vectorf(2, 6), Vectorf(4, 2));
		Line c(Vectorf(4, 2), Vectorf(2, 6));
		Line d(Vectorf(0, 3), Vectorf(1, -3));
		Line e(Vectorf(-1, 3), Vectorf(1, -3));

		REQUIRE(Line::areIntersecting(a, b));
		REQUIRE(Line::areIntersecting(a, c));
		REQUIRE(Line::areIntersecting(a, d));
		REQUIRE(Line::areIntersecting(a, e));
		REQUIRE(!Line::areIntersecting(b, d));
	}
}

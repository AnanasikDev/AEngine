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

	TEST_CASE("Line_areSegmentsIntersecting") {
		Line a(Vectorf(0, 0), Vectorf(5, 4));
		Line b(Vectorf(2, 6), Vectorf(4, 2));
		Line c(Vectorf(4, 2), Vectorf(2, 6));
		Line d(Vectorf(0, 3), Vectorf(1, -3));
		Line e(Vectorf(-1, 3), Vectorf(1, -3));
		Line f(Vectorf(-4, 3), Vectorf(-4, -10));

		REQUIRE(Line::areSegmentsIntersecting(a, b));
		REQUIRE(Line::areSegmentsIntersecting(a, c));
		REQUIRE(Line::areSegmentsIntersecting(a, d));
		REQUIRE(Line::areSegmentsIntersecting(a, e));
		REQUIRE(!Line::areSegmentsIntersecting(b, d));
		REQUIRE(!Line::areSegmentsIntersecting(a, f));
		REQUIRE(!Line::areSegmentsIntersecting(e, f));
		REQUIRE(!Line::areSegmentsIntersecting(c, f));
	}

	TEST_CASE("Line_getSegmentsIntersection") {
		// pair of diagonal intersecting lines
		Line a(Vectorf(0, 0), Vectorf(6, 4));
		Line b(Vectorf(0, 4), Vectorf(6, 0));

		Line c(Vectorf(0, 2), Vectorf(10, 2)); // horizontal line
		Line d(Vectorf(2, -1), Vectorf(2, 5)); // vertical line
		Line e(Vectorf(6, -1), Vectorf(6, 5)); // vertical line
		Line f(Vectorf(6, 100), Vectorf(6, 3)); // vetical line
		Line g(Vectorf(-2, 15), Vectorf(25, 15)); // horizontal line

		REQUIRE(Line::getLinesIntersection(a, b).value() == Vectorf(3, 2));
		REQUIRE(Line::getLinesIntersection(a, c).value() == Vectorf(3, 2));
		REQUIRE(Line::getLinesIntersection(a, d).has_value());
		REQUIRE(Line::getLinesIntersection(b, d).has_value());
		REQUIRE(!Line::getLinesIntersection(d, e).has_value());
		REQUIRE(!Line::getLinesIntersection(d, f).has_value());
		REQUIRE(!Line::getLinesIntersection(e, f).has_value());
		REQUIRE(Line::getLinesIntersection(f, g).has_value());
	}

	TEST_CASE("Line_isPointOnLine") {
		Line l1(Vectorf(0, 0), Vectorf(4, 4));
		Line l2(Vectorf(0, 0), Vectorf(0, 0));
		REQUIRE(Line::isPointOnLine(l1, Vectorf(0, 0)));
		REQUIRE(Line::isPointOnLine(l1, Vectorf(4, 4)));
		REQUIRE(Line::isPointOnLine(l1, Vectorf(2, 2)));
		REQUIRE(Line::isPointOnLine(l1, Vectorf(5, 5)));
		REQUIRE(Line::isPointOnLine(l1, Vectorf(-1, -1)));
		REQUIRE(!Line::isPointOnLine(l1, Vectorf(3, -3)));

		REQUIRE(Line::isPointOnLine(l2, Vectorf(0, 0)));
		REQUIRE(!Line::isPointOnLine(l2, Vectorf(4, 4)));
		REQUIRE(!Line::isPointOnLine(l2, Vectorf(2, 2.5f)));
		REQUIRE(!Line::isPointOnLine(l2, Vectorf(-1, -1)));
		REQUIRE(!Line::isPointOnLine(l2, Vectorf(0.1f, 0.1f)));
	}

	TEST_CASE("Line_isPointOnSegment") {
		Line l1(Vectorf(0, 0), Vectorf(4, 4));
		REQUIRE(Line::isPointOnSegment(l1, Vectorf(0, 0)));
		REQUIRE(Line::isPointOnSegment(l1, Vectorf(4, 4)));
		REQUIRE(Line::isPointOnSegment(l1, Vectorf(2, 2)));
		REQUIRE(!Line::isPointOnSegment(l1, Vectorf(5, 5)));
		REQUIRE(!Line::isPointOnSegment(l1, Vectorf(-1, -1)));
		REQUIRE(!Line::isPointOnSegment(l1, Vectorf(3, -3)));;
	}

	TEST_CASE("Line_linesEqual") {
		Line l0;
		Line l1(Vectorf(0, 0), Vectorf(5, 5));
		Line l2(Vectorf(5, 5), Vectorf(0, 0));
		Line l3(Vectorf(-10, -10), Vectorf(5, 5));
		Line l4(Vectorf(-8, -8), Vectorf(-9, -9));
		Line l5(Vectorf(-100, -99), Vectorf(0, 0));
		Line l6(Vectorf(1.5f, 4), Vectorf(0, 2.5f));
		Line l7(Vectorf(0, 0), Vectorf(-5, 5));

		//REQUIRE(!Line::linesEqual(l0, l1));
		//REQUIRE(!Line::linesEqual(l0, l2));
		//REQUIRE(!Line::linesEqual(l0, l3));
		//REQUIRE(!Line::linesEqual(l0, l4));
		//REQUIRE(!Line::linesEqual(l0, l5));

		//REQUIRE(Line::linesEqual(l1, l2));
		REQUIRE(Line::linesEqual(l1, l3));
		//REQUIRE(Line::linesEqual(l2, l3));
		/*REQUIRE(Line::linesEqual(l2, l4));
		REQUIRE(Line::linesEqual(l3, l4));

		REQUIRE(!Line::linesEqual(l1, l5));

		REQUIRE(!Line::linesEqual(l1, l6));
		REQUIRE(!Line::linesEqual(l2, l6));
		REQUIRE(!Line::linesEqual(l3, l6));
		REQUIRE(!Line::linesEqual(l4, l6));

		REQUIRE(!Line::linesEqual(l1, l7));
		REQUIRE(!Line::linesEqual(l2, l7));
		REQUIRE(!Line::linesEqual(l3, l7));
		REQUIRE(!Line::linesEqual(l4, l7));*/
	}

	TEST_CASE("Line_getSegmentBoundsIntersection") {
		Line l(Vectorf(0, 0), Vectorf(6, 3));
		Bounds b(Vectorf(0, 0), Vectorf(6, 3));

		REQUIRE((Line::segmentsEqual(Line::getSegmentBoundsIntersection(l, b).value(), l)));
	}
}

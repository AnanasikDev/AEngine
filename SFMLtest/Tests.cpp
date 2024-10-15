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

	TEST_CASE("Bounds_intersections") {
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

	TEST_CASE("Line_areLinesIntersecting") {
		// empty lines
		Line l01;
		Line l02(Vectorf(1, 2), Vectorf(1, 2));

		// Parallel lines
		Line p1(Vectorf(0, 0), Vectorf(2, 3));
		Line p2(Vectorf(2, 1), Vectorf(4, 4));
		Line p3(Vectorf(9, 13), Vectorf(17, 25));

		// Identical lines
		Line eq1(Vectorf(1, 1), Vectorf(2, 2));
		Line eq2(Vectorf(1, 1), Vectorf(0, 0));
		Line eq3(Vectorf(5, 5), Vectorf(-2, -2));
		Line eq4(Vectorf(-2, -2), Vectorf(5, 5));

		// Random lines
		Line ra1(Vectorf(-3, 2), Vectorf(0, 0));
		Line ra2(Vectorf(-3, -3), Vectorf(1, 0));
		Line ra3(Vectorf(7, 2), Vectorf(1, -2));

		// Vertical lines
		Line vert1(Vectorf(0, 0), Vectorf(0, 10));
		Line vert2(Vectorf(3, 0), Vectorf(3, 10));
		Line vert3(Vectorf(3, 5), Vectorf(3, 6));

		// Horizontal lines
		Line hor1(Vectorf(0, 0), Vectorf(7, 0));
		Line hor2(Vectorf(0, -4), Vectorf(3, -4));
		Line hor3(Vectorf(-3, 0), Vectorf(3, 0));

		REQUIRE(Line::areLinesIntersecting(l01, eq1));
		// Identical lines have intersections
		REQUIRE(Line::areLinesIntersecting(eq1, eq1));
		REQUIRE(Line::areLinesIntersecting(eq1, eq2));
		REQUIRE(Line::areLinesIntersecting(eq1, eq3));
		REQUIRE(Line::areLinesIntersecting(eq1, eq4));

		// Parallel lines have no intersection
		REQUIRE(!Line::areLinesIntersecting(p1, p2));
		REQUIRE(!Line::areLinesIntersecting(p1, p3));
		REQUIRE(!Line::areLinesIntersecting(p2, p3));

		// Random lines intersect
		REQUIRE(Line::areLinesIntersecting(ra1, ra2));
		REQUIRE(Line::areLinesIntersecting(ra1, ra3));
		REQUIRE(Line::areLinesIntersecting(ra2, ra3));

		// Vertical lines
		REQUIRE(!Line::areLinesIntersecting(vert1, vert2));
		REQUIRE(Line::areLinesIntersecting(vert2, vert3));
		REQUIRE(Line::areLinesIntersecting(vert1, ra1));
		REQUIRE(Line::areLinesIntersecting(vert1, ra2));
		REQUIRE(Line::areLinesIntersecting(vert1, ra3));
		REQUIRE(Line::areLinesIntersecting(vert2, ra1));
		REQUIRE(Line::areLinesIntersecting(vert2, ra2));
		REQUIRE(Line::areLinesIntersecting(vert2, ra3));

		// Horizontal lines
		REQUIRE(!Line::areLinesIntersecting(hor1, hor2));
		REQUIRE(!Line::areLinesIntersecting(hor2, hor3));
		REQUIRE(Line::areLinesIntersecting(hor1, ra1));
		REQUIRE(Line::areLinesIntersecting(hor1, ra2));
		REQUIRE(Line::areLinesIntersecting(hor1, ra3));
		REQUIRE(Line::areLinesIntersecting(hor2, ra1));
		REQUIRE(Line::areLinesIntersecting(hor2, ra2));
		REQUIRE(Line::areLinesIntersecting(hor2, ra3));
		REQUIRE(Line::areLinesIntersecting(hor1, vert1));
		REQUIRE(Line::areLinesIntersecting(hor1, vert2));
		REQUIRE(Line::areLinesIntersecting(hor1, vert3));
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

	TEST_CASE("Bounds_isPointInside") {
		Bounds b0;
		Bounds b1(Vectorf(1, 2), Vectorf(4, 7));

		// Empty bounds
		REQUIRE(b0.isPointInside(Vectorf(0, 0)));
		REQUIRE(!b0.isPointInside(Vectorf(0, 0.1f)));
		REQUIRE(!b0.isPointInside(Vectorf(0.1f, 0)));

		// Vertices
		REQUIRE(b1.isPointInside(Vectorf(1, 2)));
		REQUIRE(b1.isPointInside(Vectorf(4, 7)));
		REQUIRE(b1.isPointInside(Vectorf(1, 7)));
		REQUIRE(b1.isPointInside(Vectorf(4, 2)));

		// Random points outside
		REQUIRE(!b1.isPointInside(Vectorf(0, 0)));
		REQUIRE(!b1.isPointInside(Vectorf(1, 1)));
		REQUIRE(!b1.isPointInside(Vectorf(0, 7)));
		REQUIRE(!b1.isPointInside(Vectorf(2, 0)));

		// Points on edges
		REQUIRE(b1.isPointInside(Vectorf(2, 2)));
		REQUIRE(b1.isPointInside(Vectorf(1, 4)));
		REQUIRE(b1.isPointInside(Vectorf(4, 4)));
		
		// Points inside
		REQUIRE(b1.isPointInside(Vectorf(2, 6)));
		REQUIRE(b1.isPointInside(Vectorf(3, 3)));
		REQUIRE(b1.isPointInside(Vectorf(2.5f, 4.5f)));
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
		// empty lines
		Line l01;
		Line l02(Vectorf(11, 11), Vectorf(11, 11));

		// y = x
		Line l1(Vectorf(0, 0), Vectorf(5, 5));
		Line l2(Vectorf(5, 5), Vectorf(0, 0));
		Line l3(Vectorf(-10, -10), Vectorf(5, 5));
		Line l4(Vectorf(2, 2), Vectorf(-9, -9));

		// slight variation
		Line l5(Vectorf(-100, -99), Vectorf(0, 0));

		// y = x + c
		Line l6(Vectorf(1.5f, 4), Vectorf(0, 2.5f));

		// random other line
		Line l7(Vectorf(0, 0), Vectorf(-5, 6));


		// empty lines in different places are not equal
		REQUIRE(!Line::linesEqual(l01, l02));

		// empty line does not equal any non-empty line
		REQUIRE(!Line::linesEqual(l01, l1));
		REQUIRE(!Line::linesEqual(l01, l2));
		REQUIRE(!Line::linesEqual(l01, l3));
		REQUIRE(!Line::linesEqual(l01, l4));
		REQUIRE(!Line::linesEqual(l01, l5));

		// y = x lines are equal
		REQUIRE(Line::linesEqual(l1, l2));
		REQUIRE(Line::linesEqual(l1, l3));
		REQUIRE(Line::linesEqual(l2, l3));
		REQUIRE(Line::linesEqual(l2, l4));
		REQUIRE(Line::linesEqual(l3, l4));
		REQUIRE(!Line::linesEqual(l1, l5)); // almost y = x (with variation)

		// l6 is parallel to y = x. Parallel lines are not equal
		REQUIRE(!Line::linesEqual(l1, l6));
		REQUIRE(!Line::linesEqual(l2, l6));
		REQUIRE(!Line::linesEqual(l3, l6));
		REQUIRE(!Line::linesEqual(l4, l6));

		// random line, not equal to y = x
		REQUIRE(!Line::linesEqual(l1, l7));
		REQUIRE(!Line::linesEqual(l2, l7));
		REQUIRE(!Line::linesEqual(l3, l7));
		REQUIRE(!Line::linesEqual(l4, l7));
	}

	TEST_CASE("Line_segmentsEqual") {

		// empty segments
		Line e1;
		Line e2(Vectorf(3, 6), Vectorf(1, 0));

		REQUIRE(!Line::segmentsEqual(e1, e2));

		Line a1(Vectorf(1, 4), Vectorf(5, 8));
		Line a2(Vectorf(2, 5), Vectorf(4, 7));
		Line a3(Vectorf(2, 5), Vectorf(6, 9));
		Line a4(Vectorf(0, 3), Vectorf(6, 9));

		REQUIRE(!Line::segmentsEqual(a1, a2));
		REQUIRE(!Line::segmentsEqual(a1, a3));
		REQUIRE(!Line::segmentsEqual(a1, a4));

		Line b1(Vectorf(1, 4), Vectorf(5, 8));
		Line b2(Vectorf(1, 4), Vectorf(5, 8));
		Line b3(Vectorf(5, 8), Vectorf(1, 4));

		REQUIRE(Line::segmentsEqual(b1, b2));
		REQUIRE(Line::segmentsEqual(b1, b3));

		Line c1(Vectorf(0, 0), Vectorf(10, 3));
		Line c2(Vectorf(4, 2), Vectorf(-4, 3));

		REQUIRE(!Line::segmentsEqual(c1, c2));
	}

	TEST_CASE("Line_getSegmentBoundsIntersection") {
		Line l(Vectorf(0, 0), Vectorf(6, 3));
		Bounds b(Vectorf(0, 0), Vectorf(6, 3));

		REQUIRE(Line::segmentsEqual(Line::getSegmentBoundsIntersection(l, b).value(), l));
		Line l1 = Line::getSegmentBoundsIntersection(Line(l.p1 - Vectorf(5, 2.5f), l.p2 + Vectorf(4, 2)), b).value();
		std::cout << l1 << std::endl;
		REQUIRE(Line::segmentsEqual(l1, l));

		REQUIRE(Line::segmentsEqual(Line::getSegmentBoundsIntersection(Line(Vectorf(0, 0), Vectorf(0, 3)), b).value(), Line(Vectorf(0, 0), Vectorf(0, 3))));
		REQUIRE(Line::getSegmentBoundsIntersection(Line(Vectorf(-1, 0), Vectorf(-1, 3)), b).has_value() == false);
		REQUIRE(Line::getSegmentBoundsIntersection(Line(Vectorf(-1, 0), Vectorf(1, 3)), b).value().isPoint());
		REQUIRE(Line::getSegmentBoundsIntersection(Line(Vectorf(0, 4), Vectorf(2, 4)), b).has_value() == false);
		REQUIRE(Line::getSegmentBoundsIntersection(Line(Vectorf(0, 4), Vectorf(2, 3)), b).value().isPoint());
	}
}

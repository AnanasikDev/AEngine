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
		Line eq5(Vectorf(9, 9), Vectorf(10, 10));

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
		REQUIRE(Line::areLinesIntersecting(eq1, eq5));
		REQUIRE(Line::areLinesIntersecting(eq4, eq5));

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
		Line _a(Vectorf(0, 0), Vectorf(5, 4));
		Line _b(Vectorf(2, 6), Vectorf(4, 2));
		Line _c(Vectorf(4, 2), Vectorf(2, 6));
		Line _d(Vectorf(0, 3), Vectorf(1, -3));
		Line _e(Vectorf(-1, 3), Vectorf(1, -3));
		Line _f(Vectorf(-4, 3), Vectorf(-4, -10));

		REQUIRE(Line::areSegmentsIntersecting(_a, _b));
		REQUIRE(Line::areSegmentsIntersecting(_a, _c));
		REQUIRE(Line::areSegmentsIntersecting(_a, _d));
		REQUIRE(Line::areSegmentsIntersecting(_a, _e));
		REQUIRE(!Line::areSegmentsIntersecting(_b, _d));
		REQUIRE(!Line::areSegmentsIntersecting(_a, _f));
		REQUIRE(!Line::areSegmentsIntersecting(_e, _f));
		REQUIRE(!Line::areSegmentsIntersecting(_c, _f));

		Line emp1;
		Line emp2(Vectorf(3, 2), Vectorf(3, 2));
		Line a(Vectorf(1, 1), Vectorf(3, 1));
		Line b(Vectorf(4, 1), Vectorf(7, 1));
		Line c1(Vectorf(3, 0), Vectorf(4, 2));
		Line c2(Vectorf(4, 2), Vectorf(3, 0));
		Line d1(Vectorf(4, 0), Vectorf(2, 2));
		Line d2(Vectorf(2, 2), Vectorf(4, 0));
		Line e(Vectorf(6, 1), Vectorf(6, 4));
		Line f1(Vectorf(5, 0), Vectorf(5, -1));
		Line f2(Vectorf(5, -1), Vectorf(5, 0));
		Line g(Vectorf(3, -2), Vectorf(3, 3));

		REQUIRE(Line::areSegmentsIntersecting(emp2, g));
		REQUIRE(Line::areSegmentsIntersecting(emp1, a) == false);
		REQUIRE(Line::areSegmentsIntersecting(emp1, emp2) == false);
		REQUIRE(Line::areSegmentsIntersecting(emp2, d1) == false);

		REQUIRE(Line::areSegmentsIntersecting(a, b) == false);
		REQUIRE(Line::areSegmentsIntersecting(b, a) == false);
		REQUIRE(Line::areSegmentsIntersecting(a, c1) == false);
		REQUIRE(Line::areSegmentsIntersecting(a, c2) == false);
		REQUIRE(Line::areSegmentsIntersecting(a, f1) == false);
		REQUIRE(Line::areSegmentsIntersecting(g, f1) == false);
		REQUIRE(Line::areSegmentsIntersecting(g, e) == false);
		REQUIRE(Line::areSegmentsIntersecting(e, g) == false);
		REQUIRE(Line::areSegmentsIntersecting(f1, b) == false);
		REQUIRE(Line::areSegmentsIntersecting(f2, b) == false);

		REQUIRE(Line::areSegmentsIntersecting(c1, g));
		REQUIRE(Line::areSegmentsIntersecting(c2, g));
		REQUIRE(Line::areSegmentsIntersecting(c1, d1));
		REQUIRE(Line::areSegmentsIntersecting(c1, d2));
		REQUIRE(Line::areSegmentsIntersecting(c2, d1));
		REQUIRE(Line::areSegmentsIntersecting(c2, d2));
	}

	TEST_CASE("Line_areSegmentLineIntersecting") {
		Line el01;
		Line es01;
		Line es02(Vectorf(1, 1), Vectorf(1, 1));

		Line a(Vectorf(0, 0), Vectorf(5, 4));
		Line b(Vectorf(2, 6), Vectorf(4, 2));
		Line c(Vectorf(4, 2), Vectorf(2, 6));
		Line d(Vectorf(-3, 4), Vectorf(1, 4));
		Line e(Vectorf(-1, 3), Vectorf(1, -3));
		Line f(Vectorf(-4, 3), Vectorf(-4, -10));
		Line g(Vectorf(2, 4), Vectorf(4, 4));

		// Empty lines
		REQUIRE(Line::areSegmentLineIntersecting(el01, es01));
		REQUIRE(!Line::areSegmentLineIntersecting(el01, es02));

		REQUIRE(Line::areSegmentLineIntersecting(a, b));
		REQUIRE(Line::areSegmentLineIntersecting(b, a));
		REQUIRE(Line::areSegmentLineIntersecting(a, c));
		REQUIRE(Line::areSegmentLineIntersecting(b, c));
		REQUIRE(Line::areSegmentLineIntersecting(b, d));
		REQUIRE(Line::areSegmentLineIntersecting(d, d));
		REQUIRE(Line::areSegmentLineIntersecting(d, b) == false);
		REQUIRE(Line::areSegmentLineIntersecting(d, c) == false);
		REQUIRE(Line::areSegmentLineIntersecting(c, d));
		REQUIRE(Line::areSegmentLineIntersecting(d, f) == false);
		REQUIRE(Line::areSegmentLineIntersecting(d, e));
		REQUIRE(Line::areSegmentLineIntersecting(e, d) == false);
		REQUIRE(Line::areSegmentLineIntersecting(f, d) == false);
		REQUIRE(Line::areSegmentLineIntersecting(d, a) == false);
		REQUIRE(Line::areSegmentLineIntersecting(a, d));

		REQUIRE(Line::areSegmentLineIntersecting(a, g));
		REQUIRE(Line::areSegmentLineIntersecting(g, a) == false);

		REQUIRE(Line::areLinesIntersecting(d, g));
		REQUIRE(Line::areLinesIntersecting(g, d));
		REQUIRE(Line::areSegmentLineIntersecting(d, g));
		REQUIRE(Line::areSegmentLineIntersecting(g, d));
	}


	TEST_CASE("Line_getLinesIntersection") {
		Line emp0;
		Line emp1(Vectorf(2, 1), Vectorf(2, 1));
		Line a1(Vectorf(0, 1), Vectorf(2, 1));
		Line a2(Vectorf(4, 1), Vectorf(5, 1));
		Line b(Vectorf(3, 2), Vectorf(5, 2));
		Line c(Vectorf(-2, 0), Vectorf(0, 1));
		Line d(Vectorf(-1, 2), Vectorf(1, 3));
		Line e(Vectorf(1, -3), Vectorf(1, -1));
		Line f(Vectorf(2, -1), Vectorf(2, -3));
		
		// identical lines
		REQUIRE(Line::getLinesIntersection(a1, a2).value() == Vectorf(2.75f, 1));

		REQUIRE(Line::getLinesIntersection(emp0, emp1).has_value() == false);
		REQUIRE(Line::getLinesIntersection(emp0, a1).has_value() == false);
		REQUIRE(Line::getLinesIntersection(a1, b).has_value() == false);
		REQUIRE(Line::getLinesIntersection(c, d).has_value() == false);
		REQUIRE(Line::getLinesIntersection(e, f).has_value() == false);
		REQUIRE(Line::getLinesIntersection(a1, emp1).value() == Vectorf(2, 1));

		REQUIRE(Line::getLinesIntersection(a1, c).value() == Vectorf(0, 1));
		REQUIRE(Line::getLinesIntersection(a1, d).value() == Vectorf(-3, 1));
		REQUIRE(Line::getLinesIntersection(e, a1).value() == Vectorf(1, 1));
		REQUIRE(Line::getLinesIntersection(f, c).value() == Vectorf(2, 2));
	}

	TEST_CASE("Line_getSegmentsIntersection") {
		Line emp1;
		Line emp2(Vectorf(3, 2), Vectorf(3, 2));
		Line a(Vectorf(1, 1), Vectorf(3, 1));
		Line b(Vectorf(4, 1), Vectorf(7, 1));
		Line c1(Vectorf(3, 0), Vectorf(4, 2));
		Line c2(Vectorf(4, 2), Vectorf(3, 0));
		Line d1(Vectorf(4, 0), Vectorf(2, 2));
		Line d2(Vectorf(2, 2), Vectorf(4, 0));
		Line e(Vectorf(6, 1), Vectorf(6, 4));
		Line f1(Vectorf(5, 0), Vectorf(5, -1));
		Line f2(Vectorf(5, -1), Vectorf(5, 0));
		Line g(Vectorf(3, -2), Vectorf(3, 3));
		Line h(Vectorf(-1, 1), Vectorf(2, 1));

		REQUIRE(Line::areSegmentsIntersecting(emp2, g));
		REQUIRE(Line::getLinesIntersection(emp2, g).value() == Vectorf(3, 2));
		REQUIRE(Line::getSegmentsIntersection(emp2, g).value() == Vectorf(3, 2));
		REQUIRE(Line::getSegmentsIntersection(emp1, a).has_value() == false);
		REQUIRE(Line::getSegmentsIntersection(emp1, emp2).has_value() == false);
		REQUIRE(Line::getSegmentsIntersection(emp2, d1).has_value() == false);

		REQUIRE(Line::getSegmentsIntersection(a, b).has_value() == false);
		REQUIRE(Line::getSegmentsIntersection(b, a).has_value() == false);
		REQUIRE(Line::getSegmentsIntersection(a, c1).has_value() == false);
		REQUIRE(Line::getSegmentsIntersection(a, c2).has_value() == false);
		REQUIRE(Line::getSegmentsIntersection(a, f1).has_value() == false);
		REQUIRE(Line::getSegmentsIntersection(g, f1).has_value() == false);
		REQUIRE(Line::getSegmentsIntersection(g, e).has_value() == false);
		REQUIRE(Line::getSegmentsIntersection(e, g).has_value() == false);
		REQUIRE(Line::getSegmentsIntersection(f1, b).has_value() == false);
		REQUIRE(Line::getSegmentsIntersection(f2, b).has_value() == false);

		// TODO: overlapping not in a single point but in a segment, must result in the center point of overlap (now returns one of the edges of a segment)
		REQUIRE(Line::getSegmentsIntersection(a, h).has_value());

		REQUIRE(Line::getSegmentsIntersection(e, b).value() == Vectorf(6, 1));
		REQUIRE(Line::getSegmentsIntersection(b, e).value() == Vectorf(6, 1));
		REQUIRE(Line::getSegmentsIntersection(a, d1).value() == Vectorf(3, 1));
		REQUIRE(Line::getSegmentsIntersection(a, g).value() == Vectorf(3, 1));
		REQUIRE(Line::getSegmentsIntersection(c1, g).value() == Vectorf(3, 0));
		REQUIRE(Line::getSegmentsIntersection(c2, g).value() == Vectorf(3, 0));
		REQUIRE(Line::getSegmentsIntersection(c1, d1).value() == Vectorf(3 + 1./3., 2./3.));
		REQUIRE(Line::getSegmentsIntersection(c1, d2).value() == Vectorf(3 + 1./3., 2./3.));
		REQUIRE(Line::getSegmentsIntersection(c2, d1).value() == Vectorf(3 + 1./3., 2./3.));
		REQUIRE(Line::getSegmentsIntersection(c2, d2).value() == Vectorf(3 + 1./3., 2./3.));
	}

	TEST_CASE("Line_getSegmentLineIntersection") {
		Line emp1;
		Line emp2(Vectorf(3, 2), Vectorf(3, 2));
		Line a(Vectorf(1, 1), Vectorf(3, 1));
		Line b(Vectorf(4, 1), Vectorf(7, 1));
		Line c1(Vectorf(3, 0), Vectorf(4, 2));
		Line c2(Vectorf(4, 2), Vectorf(3, 0));
		Line d1(Vectorf(4, 0), Vectorf(2, 2));
		Line d2(Vectorf(2, 2), Vectorf(4, 0));
		Line e(Vectorf(6, 1), Vectorf(6, 4));
		Line f1(Vectorf(5, 0), Vectorf(5, -1));
		Line f2(Vectorf(5, -1), Vectorf(5, 0));
		Line g(Vectorf(3, -2), Vectorf(3, 3));

		REQUIRE(Line::getSegmentLineIntersection(a, b).has_value());
		REQUIRE(Line::getSegmentLineIntersection(b, a).has_value());
		REQUIRE(Line::getSegmentLineIntersection(c1, e).has_value() == false);
		REQUIRE(Line::getSegmentLineIntersection(e, c1).has_value() == false);
		REQUIRE(Line::getSegmentLineIntersection(e, Line(c1.p1 + Vectorf::up * 2, c1.p2 + Vectorf::up * 2)).value() == Vectorf(6, 4));
		REQUIRE(Line::getSegmentLineIntersection(a, d1).value() == Vectorf(3, 1));
		REQUIRE(Line::getSegmentLineIntersection(d1, a).value() == Vectorf(3, 1));
		REQUIRE(Line::getSegmentLineIntersection(b, f1).value() == Vectorf(5, 1));
		REQUIRE(Line::getSegmentLineIntersection(f1, b).has_value() == false);
		REQUIRE(Line::getSegmentLineIntersection(d1, f1).has_value() == false);
		REQUIRE(Line::getSegmentLineIntersection(f1, d1).value() == Vectorf(5, -1));
		REQUIRE(Line::getSegmentLineIntersection(e, g).has_value() == false);
		REQUIRE(Line::getSegmentLineIntersection(g, e).has_value() == false);
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

}

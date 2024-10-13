#include "Line.h"
#include "Mathf.h"
#include "SFML/Graphics.hpp"
#include "Bounds.h"

namespace aengine {

	Line::Line() {
		line = sf::VertexArray(sf::Lines, 2);
		setPoint1(Vectorf());
		setPoint2(Vectorf());
	}

	Line::Line(Vectorf pos1, Vectorf pos2) {
		line = sf::VertexArray(sf::Lines, 2);
		setPoint1(pos1);
		setPoint2(pos2);
	}

	void Line::setPoint1(Vectorf p1, sf::Color color) {
		this->p1 = p1;
		line[0].position = p1.getsf();
		line[0].color = color;
	}

	void Line::setPoint2(Vectorf p2, sf::Color color) {
		this->p2 = p2;
		line[1].position = p2.getsf();
		line[1].color = color;
	}

	bool Line::linesEqual(const Line& l1, const Line& l2) {
		Vectorf dir1 = (l1.p2 - l1.p1).vabs();
		Vectorf dir2 = (l2.p2 - l2.p1).vabs();

		bool isUndef1 = dir1 == Vectorf::zero;
		bool isUndef2 = dir2 == Vectorf::zero;

		// Exactly one line is undefined
		if (isUndef1 != isUndef2)
			return false;

		// Both are undefined and not equal
		if (isUndef1 && isUndef2 && l1.p1 != l2.p1)
			return false;

		// Check if directions are parallel
		std::cout << std::fabs(dir1.crossProduct(dir2)) << std::endl;
		if (std::fabs(dir1.crossProduct(dir2)) > 1e-6) {
			return false; // Lines are not parallel
		}

		return Line::isPointOnSegment(l1, l2.p1);
	}

	bool Line::segmentsEqual(const Line& l1, const Line& l2) {
		return l1.p1 == l2.p1 && l1.p2 == l2.p2 || l1.p1 == l2.p2 && l1.p2 == l2.p1;
	}

	float Line::getLength() const {
		return (p1 - p2).getLength();
	}

	Vectorf Line::getNormal() const {
		Vectorf v = p1 - p2;
		return Vectorf(-v.y, v.x);
	}

	Vectorf Line::asVector() const {
		return p2 - p1;
	}

	bool Line::isPoint() const {
		return p1 == p2;
	}

	Line Line::lineCircleIntersection(const Line& line, const Vectorf& circleCenter, const float circleRadius) {
		return Line(Vectorf(), Vectorf()); // NEEDS IMPLEMENTATION
	}

	bool Line::areLinesIntersecting(const Line& l1, const Line& l2) {

		bool isp1 = l1.isPoint();
		bool isp2 = l2.isPoint();
		// if both lines are indefinite (=point) OR only one line is indefinite but it doesn't lie on the other line
		if (isp1 && isp2 || isp1 && Line::isPointOnSegment(l2, l1.p1) || isp2 && Line::isPointOnSegment(l1, l2.p1)) return false;

		float a1, b1, c1, a2, b2, c2;
		std::tie(a1, b1, c1) = l1.getABC();
		std::tie(a2, b2, c2) = l2.getABC();

		float det = a1 * b2 - a2 * b1;
		if (det == 0) {
			return false; // Lines are parallel
		}
		
		return true;
	}

	std::optional<Vectorf> Line::getLinesIntersection(const Line& l1, const Line& l2) {
		float a1, b1, c1, a2, b2, c2;
		std::tie(a1, b1, c1) = l1.getABC();
		std::tie(a2, b2, c2) = l2.getABC();

		float det = a1 * b2 - a2 * b1;
		if (det == 0) {
			return std::nullopt; // Lines are parallel
		}

		float x = (b1 * c2 - b2 * c1) / det;
		float y = (a2 * c1 - a1 * c2) / det;
		return Vectorf(x, y);
	}

	bool Line::areSegmentsIntersecting(const Line& line1, const Line& line2) {

		if (Line::isPointOnSegment(line1, line2.p1) ||
			Line::isPointOnSegment(line1, line2.p2) ||
			Line::isPointOnSegment(line2, line1.p1) ||
			Line::isPointOnSegment(line2, line1.p2)) return true;

		auto v1 = line1.asVector();
		auto v2 = line2.asVector();

		auto v11 = line2.p1 - line1.p1;
		auto v12 = line2.p2 - line1.p1;

		auto v21 = line1.p1 - line2.p1;
		auto v22 = line1.p2 - line2.p1;

		float c1 = v1.crossProduct(v11);
		float c2 = v1.crossProduct(v12);
		float c3 = v2.crossProduct(v21);
		float c4 = v2.crossProduct(v22);

		if (Mathf::sign(c1) == Mathf::sign(c2)) return false;

		if (Mathf::sign(c3) == Mathf::sign(c4)) return false;

		return true;
	}

	std::optional<Vectorf> Line::getSegmentsIntersection(const Line& l1, const Line& l2) {
		if (areSegmentsIntersecting(l1, l2)) {
			return getLinesIntersection(l1, l2);
		}
		return std::nullopt;
	}

	bool Line::areSegmentBoundsIntesecting(const Line& line, const Bounds& bounds) {

		if (bounds.isPointInside(line.p1) || bounds.isPointInside(line.p2)) return true;

		auto segments = bounds.getSegments();

		for (auto segment : segments) {
			if (Line::areSegmentsIntersecting(segment, line)) return true;
		}

		return false;
	}

	std::optional<Line> Line::getSegmentBoundsIntersection(const Line& line, const Bounds& bounds) {
		
		bool p1Inside = bounds.isPointInside(line.p1);
		bool p2Inside = bounds.isPointInside(line.p2);

		if (p1Inside && p2Inside) return line;
		
		auto segments = bounds.getSegments();
		
		if (p1Inside) {
			for (auto segment : segments) {
				auto intersection = Line::getSegmentsIntersection(segment, line);
				if (intersection.has_value()) 
					return Line(line.p1, intersection.value());
			}
		}

		if (p2Inside) {
			for (auto segment : segments) {
				auto intersection = Line::getSegmentsIntersection(segment, line);
				if (intersection.has_value()) 
					return Line(line.p2, intersection.value());
			}
		}

		std::optional<Vectorf> p1 = std::nullopt;
		std::optional<Vectorf> p2 = std::nullopt;

		int i = 0;
		for (i = 0; i < segments.size(); i++) {
			auto intersection = Line::getSegmentsIntersection(segments[i], line);
			if (intersection.has_value()) {
				p1 = intersection.value();
			}
		}

		for (int j = i; j < segments.size(); j++) {
			auto intersection = Line::getSegmentsIntersection(segments[j], line);
			if (intersection.has_value()) {
				p2 = intersection.value();
			}
		}

		if (!p1.has_value() && !p2.has_value())
			return std::nullopt;

		if (!p1.has_value())
			return Line(p2.value(), p2.value());

		if (!p2.has_value())
			return Line(p1.value(), p1.value());

		return Line(p1.value(), p2.value());
	}

	bool Line::isPointOnSegment(const Line& line, const Vectorf& point) {
		if (point == line.p1 || point == line.p2) return true;
		float len = line.getLength();

		return ((line.p1 - point).normalized() == (line.p1 - line.p2) / len &&
			    (line.p2 - point).normalized() == (line.p2 - line.p1) / len);
	}

	bool Line::isPointOnLine(const Line& line, const Vectorf& point) {
		if (point == line.p1 || point == line.p2) return true;

		if (line.isPoint())
			return line.p1 == point;

		auto d1 = (point - line.p1).normalized();
		auto d2 = (point - line.p2).normalized();
		return d1 == d2 || d1 == -d2;
	}

	std::tuple<float, float, float> Line::getABC() const {
		if (p2.x - p1.x == 0) {
			// no later division, vertical line

			return std::make_tuple<float, float, float>(1 / p1.x, 0, 0);
		}

		if (p2.y - p1.y == 0) {
			// horizontal line

			return std::make_tuple<float, float, float>(0, 1 / p1.y, -1);
		}
		
		const float tan = (p2.y - p1.y) / (p2.x - p1.x);
		const float shift = p1.y - p1.x * tan;

		return std::make_tuple<float, float, float>(-tan, 1, -shift);
	}

	void Line::render(sf::RenderWindow* window, Vectorf shift, float scale, sf::Color color) {
		line[0].position = (p1 * scale + shift).getsf();
		line[1].position = (p2 * scale + shift).getsf();
		line[0].color = color;
		line[1].color = color;
		window->draw(line);
		line[0].position = p1.getsf();
		line[1].position = p2.getsf();
	}
}

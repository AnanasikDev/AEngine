#include "Line.h"
#include "Mathf.h"

namespace aengine {
	Line::Line(Vectorf pos1, Vectorf pos2) {
		this->p1 = pos1;
		this->p2 = pos2;
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

	Line Line::lineCircleIntersection(const Line& line, const Vectorf& circleCenter, const float circleRadius) {
		return Line(); // NEEDS IMPLEMENTATION
	}

	bool Line::areIntersecting(const Line& line1, const Line& line2) {

		if (Line::isPointOnLine(line1, line2.p1) ||
			Line::isPointOnLine(line1, line2.p2) ||
			Line::isPointOnLine(line2, line1.p1) ||
			Line::isPointOnLine(line2, line1.p2)) return true;

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

		//std::cout << c1 << "  " << c2 << "  " << c3 << "  " << c4 << "  " << std::endl;

		if (Mathf::sign(c1) == Mathf::sign(c2)) return false;

		if (Mathf::sign(c3) == Mathf::sign(c4)) return false;

		return true;
	}

	std::optional<Vectorf> Line::getIntersection(const Line& l1, const Line& l2) {
		float a1, b1, c1, a2, b2, c2;
		std::tie(a1, b1, c1) = l1.getABC();
		std::tie(a2, b2, c2) = l2.getABC();

		Vectorf i;

		// check if same
		if (a1 / a2 == b1 / b2) {
			// parallel

			if (c1 / c2 == a1 / a2) {
				// identical
				return (l1.p1 + l1.p2) / 2.f;
			}
		}

		// check if horizontal
		if (a1) {
			i.x = (c1 / b1 - c2 / b2) / a2;
		}

		
		// calculate intersection
		i.y = (c1 / a1 - c2 / a2) / (b2 / a2 - b1 / a1);
		i.x = (-b1 * i.y - c1) / a1;

		return std::make_optional<Vectorf>(i);
	}

	Line Line::lineBoundsIntersection(const Line& line, const Bounds& bounds) {
		return Line();
	}

	bool Line::isPointOnLine(const Line& line, const Vectorf& point) {
		if (point == line.p1 || point == line.p2) return true;
		float len = line.getLength();

		return ((line.p1 - point).normalized() == (line.p1 - line.p2) / len &&
			    (line.p2 - point).normalized() == (line.p2 - line.p1) / len);
	}

	std::tuple<float, float, float> Line::getABC() const {
		if (p2.x - p1.x == 0) {
			// no later division, vertical line

			return std::make_tuple<float, float, float>(1 / p1.x, 0, 0);
		}

		if (p2.y - p1.y == 0) {
			// horizontal line

			return std::make_tuple<float, float, float>(0, 1 / p1.y, 0);
		}
		
		const float tan = (p2.y - p1.y) / (p2.x - p1.x);
		const float shift = p1.y - p1.x * tan;

		return std::make_tuple<float, float, float>(-tan, 1, -shift);
	}
}

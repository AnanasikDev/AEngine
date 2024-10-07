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

	Line Line::lineBoundsIntersection(const Line& line, const Bounds& bounds) {
		return Line();
	}

	bool Line::isPointOnLine(const Line& line, const Vectorf& point) {
		if (point == line.p1 || point == line.p2) return true;
		float len = line.getLength();

		std::cout << (line.p1 - point).normalized() << std::endl << (line.p1 - line.p2) / len << std::endl <<
			(line.p2 - point).normalized() << std::endl << (line.p2 - line.p1) / len << std::endl;

		return ((line.p1 - point).normalized() == (line.p1 - line.p2) / len &&
			    (line.p2 - point).normalized() == (line.p2 - line.p1) / len);
	}
}

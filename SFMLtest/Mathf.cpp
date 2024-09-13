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
	
	Vectorf Mathf::tanToVector(float tangent) {
		return Vectorf(1, tangent).normalized();
	}

	Line Mathf::LineCircleIntersection(const Line& line, const Vectorf& circleCenter, const float circleRadius) {
		return Line();
	}
}
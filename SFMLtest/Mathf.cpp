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

	int Mathf::Sign(float val) {
		return val >= 0 ? 1 : -1;
	}

	float Mathf::Clamp(float value, float min, float max) {
		return value > max ? max : (value < min ? min : value);
	}

	float Mathf::ClampMin(float value, float min) {
		return value < min ? min : value;
	}

	float Mathf::ClampMax(float value, float max) {
		return value > max ? max : value;
	}

	float Mathf::Remainder(float value, float divider){
		return remainderf(value, divider);
	}

	float Mathf::Repeat(float value, float min, float max) {
		return value < min ? max - Remainder(min - value, max - min) : (value > max ? min + Remainder(value - max, max - min) : value);
	}
}
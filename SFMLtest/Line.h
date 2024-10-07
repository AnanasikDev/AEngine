#pragma once

#include "Vector.h"

namespace aengine {

	class Bounds;

	class Line {
	public:
		Vectorf p1;
		Vectorf p2;
		bool isEmpty = false;

		Line() = default;
		Line(Vectorf pos1, Vectorf pos2);

		Vectorf getNormal() const;
		inline float getLength() const;

		Vectorf asVector() const;

		static Line lineCircleIntersection(const Line& line, const Vectorf& circleCenter, const float circleRadius);

		static bool areIntersecting(const Line& line1, const Line& line2);

		static Line lineBoundsIntersection(const Line& line, const Bounds& bounds);

		static bool isPointOnLine(const Line& line, const Vectorf& point);
	};
}

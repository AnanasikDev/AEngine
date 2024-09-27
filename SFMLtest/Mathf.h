#pragma once

#include "Vector.h"

namespace aengine {

	class Line {
	public:
		Vectorf p1;
		Vectorf p2;
		bool isEmpty = false;

		Line() = default;
		Line(Vectorf pos1, Vectorf pos2);

		Vectorf getNormal() const;
		inline float getLength() const;
	};

	class Mathf {
	public:
		/// <summary>
		/// Based on angle tangent returns a vectorf
		/// with scale of 1 for the corresponding angle.
		/// </summary>
		static Vectorf tanToVector(float tangent);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="line"></param>
		/// <param name="circleCenter"></param>
		/// <param name="circleRadius"></param>
		/// <returns></returns>
		static Line LineCircleIntersection(const Line& line, const Vectorf& circleCenter, const float circleRadius);

		/// <summary>
		/// Returns -1 or 1 depending on sign of val
		/// </summary>
		static int Sign(float val);

		static float Clamp(float value, float min, float max);

		static float ClampMin(float value, float min);

		static float ClampMax(float value, float max);

		static float Repeat(float value, float min, float max);

		static float Remainder(float value, float divider);
	};
}
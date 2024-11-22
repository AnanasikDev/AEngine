#pragma once

#include "Vector.h"

namespace aengine {

	struct Mathf {
		static const float PI;
		static const float E;
		static const float PHI;

		/// <summary>
		/// Based on angle tangent returns a vectorf
		/// with scale of 1 for the corresponding angle.
		/// </summary>
		static Vectorf tanToVector(float tangent);

		/// <summary>
		/// Returns -1 or 1 depending on sign of val
		/// </summary>
		static int sign(float val);

		static float clamp(float value, float min, float max);
		
		static float clamp01(float value);

		static float clampMin(float value, float min);

		static float clampMax(float value, float max);

		static float repeat(float value, float min, float max);

		static float repeat(float value, float length);

		static float pingpong(float value, float min, float max);

		static float pingpong(float value, float length);

		/// <summary>
		/// Returns remainder from dividing value by divider
		/// </summary>
		static float remainder(float value, float divider);

		/// <summary>
		/// Floors the value to the nearest number, divisible by scale
		/// </summary>
		static float pixelate(float value, float scale);

		/// <summary>
		/// Lineraly lerps between values a and b by an unclamped value t.
		/// </summary>
		static float lerp(float a, float b, float t);

		static float easeLinear(float v);

		static float easeInBack(float v);
		static float easeOutBack(float v);
		static float easeInOutBack(float v);

		static float easeInSine(float v);
		static float easeOutSine(float v);
		static float easeInOutSine(float v);
		
		static float easeInBounce(float v);
		static float easeOutBounce(float v);
		static float easeInOutBounce(float v);
	};
}
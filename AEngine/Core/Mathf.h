#pragma once

#include "Vector.h"

namespace aengine {

	const float PI = 3.1415926f;
	const float E = 2.7182818f;
	const float PHI = 1.6180339f;

	/// <summary>
	/// Based on angle tangent returns a vectorf
	/// with scale of 1 for the corresponding angle.
	/// </summary>
	Vectorf tanToVector(float tangent);

	/// <summary>
	/// Returns -1 or 1 depending on sign of val
	/// </summary>
	int sign(float val);

	float clamp(float value, float min, float max);
		
	float clamp01(float value);

	float clampMin(float value, float min);

	float clampMax(float value, float max);

	float repeat(float value, float min, float max);

	float repeat(float value, float length);

	float pingpong(float value, float min, float max);

	float pingpong(float value, float length);

	/// <summary>
	/// Returns remainder from dividing value by divider
	/// </summary>
	float remainder(float value, float divider);

	/// <summary>
	/// Floors the value to the nearest number, divisible by scale
	/// </summary>
	float pixelate(float value, float scale);

	/// <summary>
	/// Lineraly lerps between values a and b by an unclamped value t.
	/// </summary>
	float lerp(float a, float b, float t);

	struct Ease
	{
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

		static float easeInElastic(float v);
		static float easeOutElastic(float v);
		static float easeInOutElastic(float v);
	};
}
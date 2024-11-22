#include "Mathf.h"

namespace aengine {

	Vectorf Mathf::tanToVector(float tangent) {
		return Vectorf(1, tangent).normalized();
	}

	int Mathf::sign(float val) {
		return val >= 0 ? 1 : -1;
	}

	float Mathf::clamp(float value, float min, float max) {
		return value > max ? max : (value < min ? min : value);
	}

	float Mathf::clampMin(float value, float min) {
		return value < min ? min : value;
	}

	float Mathf::clampMax(float value, float max) {
		return value > max ? max : value;
	}

	float Mathf::remainder(float value, float divider){
		return remainderf(value, divider);
	}

	float Mathf::repeat(float value, float min, float max) {
		return value < min ? max - remainder(min - value, max - min) : (value > max ? min + remainder(value - max, max - min) : value);
	}

	float Mathf::repeat(float value, float length) {
		return repeat(value, 0, length);
	}

	float Mathf::pingpong(float value, float min, float max) {
		float len = max - min;
		float rem = Mathf::remainder(value, len * 2.);
		if (rem < 0) rem = len * 2. + rem; // convert negative remainder to positive
		if (rem < len) return min + rem;
		else return max - (rem - len);
	}

	float Mathf::pingpong(float value, float length) {
		return pingpong(value, 0, length);
	}

	float Mathf::pixelate(float value, float scale) {
		float rem = remainder(value, scale);
		if (abs(rem) < scale / 2.f) return value - rem;
		else return value - rem + scale * sign(value);
	}

	float Mathf::lerp(float a, float b, float t) {
		return a + (b - a) * t;
	}
}
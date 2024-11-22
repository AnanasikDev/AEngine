#include "Mathf.h"

namespace aengine {

	const float Mathf::PI  = 3.1415926f;
	const float Mathf::E   = 2.7182818f;
	const float Mathf::PHI = 1.6180339f;

	Vectorf Mathf::tanToVector(float tangent) {
		return Vectorf(1, tangent).normalized();
	}

	int Mathf::sign(float val) {
		return val >= 0 ? 1 : -1;
	}

	float Mathf::clamp(float value, float min, float max) {
		return value > max ? max : (value < min ? min : value);
	}

	float Mathf::clamp01(float value) {
		return clamp(value, 0., 1.);
	}

	float Mathf::clampMin(float value, float min) {
		return value < min ? min : value;
	}

	float Mathf::clampMax(float value, float max) {
		return value > max ? max : value;
	}

	float Mathf::remainder(float value, float divider) {
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

	float Mathf::easeLinear(float v) {
		return v;
	}

	float Mathf::easeInOutBack(float v){
		const float c1 = 1.70158;
		const float c2 = c1 * 1.525;

		return v < 0.5
		  ? (pow(2 * v, 2) * ((c2 + 1) * 2 * v - c2)) / 2
		  : (pow(2 * v - 2, 2) * ((c2 + 1) * (v * 2 - 2) + c2) + 2) / 2;
	}

	float Mathf::easeInBack(float v) {
		const float c1 = 1.70158;
		const float c3 = c1 + 1;

		return c3 * pow(v, 3) - c1 * pow(v, 2);
	}

	float Mathf::easeOutBack(float v) {
		const float c1 = 1.70158;
		const float c3 = c1 + 1;

		return 1 + c3 * pow(v - 1, 3) - c1 * pow(v - 1, 2);
	}

	float Mathf::easeInSine(float v) {
		return 1 - cos(v * PI / 2);
	}

	float Mathf::easeOutSine(float v) {
		return sin(v * PI / 2);
	}

	float Mathf::easeInOutSine(float v) {
		return -(cos(PI * v) - 1) / 2;
	}

	float Mathf::easeInBounce(float v) {
		const float n1 = 7.5625;
		const float d1 = 2.75;

		if (v < 1 / d1) {
			return n1 * v * v;
		}
		else if (v < 2 / d1) {
			return n1 * (v -= 1.5 / d1) * v + 0.75;
		}
		else if (v < 2.5 / d1) {
			return n1 * (v -= 2.25 / d1) * v + 0.9375;
		}
		else {
			return n1 * (v -= 2.625 / d1) * v + 0.984375;
		}
	}

	float Mathf::easeOutBounce(float v) {
		const float n1 = 7.5625;
		const float d1 = 2.75;

		if (v < 1 / d1) {
			return n1 * v * v;
		}
		else if (v < 2 / d1) {
			return n1 * (v -= 1.5 / d1) * v + 0.75;
		}
		else if (v < 2.5 / d1) {
			return n1 * (v -= 2.25 / d1) * v + 0.9375;
		}
		else {
			return n1 * (v -= 2.625 / d1) * v + 0.984375;
		}
	}

	float Mathf::easeInOutBounce(float v) {
		return v < 0.5
			? (1 - easeOutBounce(1 - 2 * v)) / 2
			: (1 + easeOutBounce(2 * v - 1)) / 2;
	}
}
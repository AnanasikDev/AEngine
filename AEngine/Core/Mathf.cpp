#include "Mathf.h"

namespace aengine {

	Vectorf tanToVector(float tangent) {
		return Vectorf(1, tangent).normalized();
	}

	int sign(float val) {
		return val >= 0 ? 1 : -1;
	}

	float clamp(float value, float min, float max) {
		return value > max ? max : (value < min ? min : value);
	}

	float clamp01(float value) {
		return clamp(value, 0., 1.);
	}

	float clampMin(float value, float min) {
		return value < min ? min : value;
	}

	float clampMax(float value, float max) {
		return value > max ? max : value;
	}

	float remainder(float value, float divider) {
		return remainderf(value, divider);
	}

	float repeat(float value, float min, float max) {
		return value < min ? max - remainder(min - value, max - min) : (value > max ? min + remainder(value - max, max - min) : value);
	}

	float repeat(float value, float length) {
		return repeat(value, 0, length);
	}

	float pingpong(float value, float min, float max) {
		float len = max - min;
		float rem = remainder(value, len * 2.);
		if (rem < 0) rem = len * 2. + rem; // convert negative remainder to positive
		if (rem < len) return min + rem;
		else return max - (rem - len);
	}

	float pingpong(float value, float length) {
		return pingpong(value, 0, length);
	}

	float pixelate(float value, float scale) {
		float rem = remainder(value, scale);
		if (abs(rem) < scale / 2.f) return value - rem;
		else return value - rem + scale * sign(value);
	}

	float lerp(float a, float b, float t) {
		return a + (b - a) * t;
	}

	float Ease::easeLinear(float v) {
		return v;
	}

	float Ease::easeInOutBack(float v){
		const float c1 = 1.70158;
		const float c2 = c1 * 1.525;

		return v < 0.5
		  ? (pow(2 * v, 2) * ((c2 + 1) * 2 * v - c2)) / 2
		  : (pow(2 * v - 2, 2) * ((c2 + 1) * (v * 2 - 2) + c2) + 2) / 2;
	}

	float Ease::easeInBack(float v) {
		const float c1 = 1.70158;
		const float c3 = c1 + 1;

		return c3 * pow(v, 3) - c1 * pow(v, 2);
	}

	float Ease::easeOutBack(float v) {
		const float c1 = 1.70158;
		const float c3 = c1 + 1;

		return 1 + c3 * pow(v - 1, 3) - c1 * pow(v - 1, 2);
	}

	float Ease::easeInSine(float v) {
		return 1 - cos(v * PI / 2);
	}

	float Ease::easeOutSine(float v) {
		return sin(v * PI / 2);
	}

	float Ease::easeInOutSine(float v) {
		return -(cos(PI * v) - 1) / 2;
	}

	float Ease::easeInBounce(float v) {
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

	float Ease::easeOutBounce(float v) {
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

	float Ease::easeInOutBounce(float v) {
		return v < 0.5
			? (1 - easeOutBounce(1 - 2 * v)) / 2
			: (1 + easeOutBounce(2 * v - 1)) / 2;
	}

	float Ease::easeInElastic(float v) {
		const float c4 = (2 * PI) / 3;

		return v == 0
			? 0
			: (v == 1
			? 1
			: -pow(2, 10 * v - 10) * sin((v * 10 - 10.75) * c4));
	}

	float Ease::easeOutElastic(float v) {
		const float c4 = (2 * PI) / 3;

		return v == 0
			? 0
			: (v == 1
			? 1
			: pow(2, -10 * v) * sin((v * 10 - 0.75) * c4) + 1);
	}

	float Ease::easeInOutElastic(float v) {
		const float c5 = (2 * PI) / 4.5;

		return v == 0
			? 0
			: (v == 1
			? 1
			: (v < 0.5
			? -(pow(2, 20 * v - 10) * sin((20 * v - 11.125) * c5)) / 2
			: (pow(2, -20 * v + 10) * sin((20 * v - 11.125) * c5)) / 2 + 1));
	}

	float Ease::easeInCubic(float v) {
		return v * v * v;
	}

	float Ease::easeOutCubic(float v) {
		return 1 - pow(1 - v, 3);
	}

	float Ease::easeInOutCubic(float v) {
		return v < 0.5 ? 4 * v * v * v : 1 - pow(-2 * v + 2, 3) / 2;
	}
}
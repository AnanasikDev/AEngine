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
}
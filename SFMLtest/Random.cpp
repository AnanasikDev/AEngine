#include "Random.h"
#include <random>

namespace aengine {
	float Random::getFloat() {
		return ((float)rand() / RAND_MAX);
	}

	float Random::getFloat(float min, float max) {
		return getFloat() * (max - min) + min;
	}

	int Random::getInt(int min, int max) {
		return std::round(getFloat() * (max - min) + min);
	}
}

#include "Random.h"
#include "db_perlin.hpp"
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

	float Random::perlin1D(float x) {
		return db::perlin(x);
	}

	float Random::perlin2D(float x, float y) {
		return db::perlin(x, y);
	}
}

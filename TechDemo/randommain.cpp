#include "Core/Engine.h"

constexpr float delta = 0.05f;
constexpr int calls = 100000;

constexpr float max = 1.;
constexpr int parts = (int)(max / delta);

int main2() {
	std::array<int, parts> values;

	for (int p = 0; p < parts; p++) {
		values[p] = 0;
	}

	for (int i = 0; i < calls; i++) {
		float val = aengine::Random::getFloat(0, max);
		for (int p = 0; p < parts; p++) {
			if (val < (p + 1) * delta) {
				values[p]++;
				break;
			}
		}
	}

	for (int p = 0; p < parts; p++) {
		std::cout << p << " (" << p * delta << " - " << (p + 1) * delta << "): " << values[p] << std::endl;
	}

	return 0;
}

#pragma once
#include <cstdint>

namespace aengine {
	class Time {
	private:
		static int deltaTimeMs;
		static float timeScale;
		static uint64_t lastTime;

	public:

		static int getDeltaTimeMs();
		static float getTimeScale();
		static void setTimeScale(float scale);

		static uint64_t getTime();

		static void Init();
		static void Update();
	};
}
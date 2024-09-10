#include "Time.h"
#include <chrono>

namespace aengine {

	int Time::deltaTimeMs = 0;
	float Time::timeScale = 1.f;
	uint64_t Time::lastTime = 0;

	int Time::getDeltaTimeMs() {
		return deltaTimeMs;
	}

	float Time::getTimeScale() {
		return timeScale;
	}

	void Time::setTimeScale(float scale) {
		timeScale = scale;
	}

	uint64_t Time::getTime(){
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	void Time::Init() {
		lastTime = getTime();
	}

	void Time::Update() {
		auto now = getTime();
		deltaTimeMs = (now - lastTime) * timeScale;
		lastTime = now;
	}
}
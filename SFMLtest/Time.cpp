#include "Time.h"
#include <chrono>
#include "List.h"

namespace aengine {

	float Time::deltaTime = 0;
	float Time::fixedDeltaTime = 0;
	float Time::timeScale = 1.f;
	uint64_t Time::lastUpdate = 0;
	uint64_t Time::lastFixedUpdate = 0;
	std::vector<Time::Coroutine> Time::coroutines;

	float Time::getDeltaTime() {
		return deltaTime;
	}

	float Time::getFixedDeltaTime() {
		return fixedDeltaTime;
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
		lastUpdate = getTime();
		lastFixedUpdate = getTime();
	}

	void Time::Update() {
		auto now = getTime();
		deltaTime = (now - lastUpdate) * timeScale / 1000.f;
		fixedDeltaTime = (now - lastFixedUpdate) * timeScale / 1000.f;
		lastUpdate = now;
		// lastFixedUpdate is updated in RecordFixedUpdate

		for (int i = 0; i < coroutines.size(); i++) {

			coroutines[i].waitingTime += deltaTime;
			
			if (!coroutines[i].invoked) {
				// never been invoked, try for the first time
				if (coroutines[i].waitingTime >= coroutines[i].startDelay) {
					coroutines[i].Execute();

					// if not repetitive, delete
					if (coroutines[i].repeating == false) {
						List::RemoveAt(coroutines, i);
					}
				}
			}
			else {
				// has already been invoked hence repetitive
				if (coroutines[i].waitingTime >= coroutines[i].delay) {
					coroutines[i].Execute();
				}
			}
		}
	}

	void Time::RecordFixedUpdate() {
		lastFixedUpdate = getTime();
	}

	void Time::Coroutine::Execute() {
		this->func();
		invoked = true;
		waitingTime = 0;
	}

	void Time::Invoke(std::function<void()> func, float delaySeconds) {
		auto cor = Coroutine();
		cor.func = func;
		cor.startDelay = delaySeconds;
		cor.repeating = false;
		coroutines.push_back(cor);
	}

	void Time::InvokeRepeating(std::function<void()> func, float startDelaySeconds, float delaySeconds) {
		auto cor = Coroutine();
		cor.func = func;
		cor.startDelay = startDelaySeconds;
		cor.delay = delaySeconds;
		cor.repeating = true;
		coroutines.push_back(cor);
	}
}
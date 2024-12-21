#include "Time.h"
#include <chrono>
#include "List.h"
#include <mutex>

namespace aengine {

	float Time::deltaTime = 0;
	float Time::fixedDeltaTime = 0;
	float Time::timeSinceStartup = 0;
	std::uint64_t Time::startupTime = 0;
	float Time::timeScale = 1.f;
	float Time::lastUpdate = 0;
	float Time::lastFixedUpdate = 0;
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

	void Time::computeTime(){
		timeSinceStartup = (getTimeSinceUNIX() - startupTime) / 1000.0f;
	}

	float Time::getTime() {
		return timeSinceStartup;
	}

	std::uint64_t Time::getTimeSinceUNIX() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	void Time::init() {
		startupTime = getTimeSinceUNIX();
		lastUpdate = getTime();
		lastFixedUpdate = getTime();
	}

	void Time::update() {

		computeTime(); 

		float now = getTime();
		deltaTime = (now - lastUpdate) * timeScale;
		fixedDeltaTime = (now - lastFixedUpdate) * timeScale;
		lastUpdate = now;
		// lastFixedUpdate is updated in RecordFixedUpdate

		for (auto cor = coroutines.begin(); cor != coroutines.end(); ) {
			cor->waitingTime += deltaTime;
			if (!cor->invoked) {
				// never been invoked, try for the first time
				if (cor->waitingTime >= cor->startDelay) {
					cor->Execute();

					// if not repetitive, delete
					if (cor->repeating == false) {
						cor = coroutines.erase(cor);
						continue;
					}
				}
			}
			else {
				// has already been invoked hence repetitive
				if (cor->waitingTime >= cor->delay) {
					cor->Execute();
				}
			}
			cor++;
		}
	}

	void Time::recordFixedUpdate() {
		lastFixedUpdate = getTime();
	}

	void Time::Coroutine::Execute() {
		invoked = true;
		waitingTime = 0;
		this->func();
	}

	void Time::invoke(std::function<void()> func, float delaySeconds) {
		auto cor = Coroutine();
		cor.func = func;
		cor.startDelay = delaySeconds;
		cor.repeating = false;
		coroutines.push_back(cor);
	}

	void Time::invokeRepeating(std::function<void()> func, float startDelaySeconds, float delaySeconds) {
		auto cor = Coroutine();
		cor.func = func;
		cor.startDelay = startDelaySeconds;
		cor.delay = delaySeconds;
		cor.repeating = true;
		coroutines.push_back(cor);
	}

	std::string Time::getCurrentLocalTime(const std::string& format) {
		// Get the current time
		auto now = std::chrono::system_clock::now();
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);

		// Convert to tm structure in a thread-safe way
		std::tm local_tm;
		{
			std::mutex mtx;
			std::lock_guard<std::mutex> lock(mtx);
			localtime_s(&local_tm, &now_time); // thread-safe version of localtime
		}

		// Format the time as a string
		std::ostringstream oss;
		oss << std::put_time(&local_tm, format.c_str());
		return oss.str();
	}

}
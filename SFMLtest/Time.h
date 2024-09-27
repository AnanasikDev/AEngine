#pragma once

#include <cstdint>
#include <functional>
#include <vector>

namespace aengine {
	class Time {
	public:
		class Coroutine {
		public:
			bool repeating = false;
			/// <summary>
			/// Whether the coroutine has been invoked at least once.
			/// </summary>
			bool invoked = false;
			float delay;
			float startDelay = delay;
			float waitingTime = 0;
			std::function<void()> func;
			void Execute();
		};

	private:
		/// <summary>
		/// Time between previous frame and current one in seconds.
		/// </summary>
		static float deltaTime;

		/// <summary>
		/// Time between previous physics FixedUpdate and current frame in seconds.
		/// </summary>
		static float fixedDeltaTime;
		static float timeScale;
		static uint64_t lastUpdate;
		static uint64_t lastFixedUpdate;

		static std::vector<Time::Coroutine> coroutines;

	public:
		/// <summary>
		/// Returns time between previous frame and current one in seconds.
		/// </summary>
		static float getDeltaTime();
		/// <summary>
		/// Returns time between previous physics FixedUpdate and current frame in seconds.
		/// </summary>
		static float getFixedDeltaTime();
		static float getTimeScale();
		static void setTimeScale(float scale);

		static uint64_t getTime();

		static void Init();
		static void Update();

		/// <summary>
		/// Updates lastFixedUpdate variable
		/// </summary>
		static void RecordFixedUpdate();

		static void Invoke(std::function<void()> func, float delaySeconds);
		static void InvokeRepeating(std::function<void()> func, float startDelaySeconds, float delaySeconds);
	};
}
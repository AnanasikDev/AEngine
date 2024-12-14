#pragma once

#include <cstdint>
#include <functional>
#include <vector>
#include <string>

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

		/// <summary>
		/// Time since startup of the application in seconds.
		/// </summary>
		static float timeSinceStartup;

		/// <summary>
		/// Time of the startup of the application since UNIX in milliseconds.
		/// </summary>
		static std::uint64_t startupTime;

		static float timeScale;
		static float lastUpdate;
		static float lastFixedUpdate;

		static std::vector<Time::Coroutine> coroutines;

		/// <summary>
		/// Computes current time in seconds, caches the result in the variable timeSinceStartup which is can be accessed using getTime().
		/// </summary>
		static void computeTime();

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

		/// <summary>
		/// Returns time in seconds since application startup (timeSinceStartup)
		/// </summary>
		/// <returns></returns>
		static float getTime();

		/// <summary>
		/// Returns time in milliseconds from UNIX
		/// </summary>
		static std::uint64_t getTimeSinceUNIX();

		static void init();

		/// <summary>
		/// Updated all values, runs coroutines
		/// </summary>
		static void update();

		/// <summary>
		/// Updates lastFixedUpdate variable
		/// </summary>
		static void recordFixedUpdate();

		static void invoke(std::function<void()> func, float delaySeconds);

		static void invokeRepeating(std::function<void()> func, float startDelaySeconds, float delaySeconds);

		static std::string getCurrentLocalTime(const std::string& format);
	};
}
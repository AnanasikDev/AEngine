#pragma once

#include <vector>
#include <array>
#include "Vector.h"

namespace aengine {
	class Random {
	public:

		static void init();

		/// <summary>
		/// Generates random float in range [0, 1]
		/// </summary>
		static float getFloat();

		/// <summary>
		/// Generates random float in range [min, max]
		/// </summary>
		static float getFloat(float min, float max);

		/// <summary>
		/// Generates random int in range [min, max]
		/// </summary>
		static int getInt(int min, int max);

		/// <summary>
		/// Returns random element from the given vector
		/// </summary>
		template <typename T>
		static T take(const std::vector<T>& vec) {
			return vec[getFloat(0, vec.size() - 1)];
		}

		/// <summary>
		/// Returns random element from the given array
		/// </summary>
		template <typename T, int length>
		static T take(const std::array<T, length>& arr) {
			return arr[getFloat(0, arr.size() - 1)];
		}

		static float perlin1D(float x);
		static float perlin2D(float x, float y);

		template <typename T>
		static Vector<T> getVector(float min = -1., float max = 1.) {
			return Vector<T>(getFloat(min, max), getFloat(min, max));
		}
	};
}

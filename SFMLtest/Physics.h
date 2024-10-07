#pragma once

#include "Bounds.h"
#include "Vector.h"

namespace aengine {

	class CircleCollider;
	class RectCollider;

	class Physics {
	public:
		static const float g;

		/// <summary>
		/// Second-long influence equals (1 - airResistance) ^ (1000 / fixedUpdateIntervalMs):
		/// With default value of 0.002f it is 0.998 ^ 50 = 0.905 ~ -10% of velocity per second
		/// </summary>
		static const float airResistance;

		/// <summary>
		/// Interval between FixedUpdate calls in milliseconds. It is highly not recommended to change this value as it might cause unexpected behaviour, inaccuracy or glitches.
		/// </summary>
		static const int fixedUpdateIntervalMs;

		static std::pair<Bounds, Vectorf> getOverlap(const CircleCollider* c1, const CircleCollider* c2);
		static std::pair<Bounds, Vectorf> getOverlap(const RectCollider* c1,   const CircleCollider* c2);
		static std::pair<Bounds, Vectorf> getOverlap(const RectCollider* c1,   const RectCollider* c2);
	};
}
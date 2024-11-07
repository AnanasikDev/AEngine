#pragma once

#include "Bounds.h"
#include "Vector.h"
#include "Mathf.h"

namespace aengine {

	class Collider;
	class CircleCollider;
	class RectCollider;
	class Line;

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

		/// <summary>
		/// Casts a segment and returns a vector containing all colliders intersected with it
		/// </summary>
		static std::vector<Collider*> segmentCastAll(const Line& line);
	};
}
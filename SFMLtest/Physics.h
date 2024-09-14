#pragma once

#include "Bounds.h"

namespace aengine {

	class CircleCollider;
	class RectCollider;

	class Physics {
	public:
		static const float g;
		static const float airResistance;
		static const int fixedUpdateIntervalMs;

		static Bounds getOverlap(const CircleCollider* c1, const CircleCollider* c2);
		static Bounds getOverlap(const RectCollider* c1,   const CircleCollider* c2);
		static Bounds getOverlap(const RectCollider* c1,   const RectCollider* c2);
	};
}
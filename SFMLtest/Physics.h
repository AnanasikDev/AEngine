#pragma once

#include "Bounds.h"
#include "Vector.h"

namespace aengine {

	class CircleCollider;
	class RectCollider;

	class Physics {
	public:
		static const float g;
		static const float airResistance;
		static const int fixedUpdateIntervalMs;

		static std::pair<Bounds, Vectorf> getOverlap(const CircleCollider* c1, const CircleCollider* c2);
		static std::pair<Bounds, Vectorf> getOverlap(const RectCollider* c1,   const CircleCollider* c2);
		static std::pair<Bounds, Vectorf> getOverlap(const RectCollider* c1,   const RectCollider* c2);
	};
}
#pragma once

namespace aengine {

	class CircleCollider;
	class RectCollider;
	class CollisionInfo;

	class Physics {
	public:
		static const float g;
		static const float airResistance;
		static const int fixedUpdateIntervalMs;

		static bool AreOverlapping(const CircleCollider* c1, const CircleCollider* c2, CollisionInfo* outInfo);
		static bool AreOverlapping(const RectCollider* c1, const CircleCollider* c2, CollisionInfo* outInfo);
		static bool AreOverlapping(const RectCollider* c1, const RectCollider* c2, CollisionInfo* outInfo);
	};
}
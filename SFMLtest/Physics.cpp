#include "Collider.h"
#include "CollisionInfo.h"
#include "Vector.h"
#include "Physics.h"

namespace aengine {
	const float Physics::g = -9.81f;
	const float Physics::airResistance = 0.045f;

	bool Physics::AreOverlapping(const CircleCollider* c1, const CircleCollider* c2, CollisionInfo* outInfo) {
		Vectorf n = (c2->center - c1->center);
		float d = n.Magnitude();
		bool b = d <= c1->radius + c2->radius;
		if (b)
			outInfo = new CollisionInfo(n, (c1->center + c2->center) / 2.f); // pos temp calculation
		return b;
	}

	bool Physics::AreOverlapping(const RectCollider* c1, const CircleCollider* c2, CollisionInfo* outInfo) {
		throw std::exception("Non-implemented function Physics::AreOverlapping (2) cannot be invoked.");
		return false;
	}

	bool Physics::AreOverlapping(const RectCollider* c1, const RectCollider* c2, CollisionInfo* outInfo) {
		throw std::exception("Non-implemented function Physics::AreOverlapping (3) cannot be invoked.");
		return false;
	}
}
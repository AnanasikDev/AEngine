#include "Collider.h"
#include "Vector.h"
#include "Physics.h"
#include "Mathf.h"
#include <iostream>

namespace aengine {
	const float Physics::g = -9.81f;
	const float Physics::airResistance = 0.02f;
	const int Physics::fixedUpdateIntervalMs = 20;

	std::pair<Bounds, Vectorf> Physics::getOverlap(const CircleCollider* c1, const CircleCollider* c2) {
		Vectorf delta = (c2->worldCenter - c1->worldCenter);
		float distance = delta.getLength();
		bool areover = distance <= c1->radius + c2->radius;
		Bounds bounds;
		// TEMPORARY IMPLEMENTATION
		bounds.setCenterAndSize((c1->worldCenter + c2->worldCenter) / 2.f, Vectorf::one);
		return std::make_pair(bounds, delta);
	}

	std::pair<Bounds, Vectorf> Physics::getOverlap(const RectCollider* c1, const CircleCollider* c2) {
		throw std::exception("Non-implemented function Physics::AreOverlapping (2) cannot be invoked.");
		
		return std::make_pair<Bounds, Vectorf>(Bounds(), Vectorf());
	}

	std::pair<Bounds, Vectorf> Physics::getOverlap(const RectCollider* c1, const RectCollider* c2) {
		Vectorf normal;

		Bounds bounds = Bounds::getIntersectionBounds(c1->bounds, c2->bounds);
		Vectorf diff = c1->worldCenter - c2->worldCenter;
		Vectorf size = bounds.getSize();

		if (size.x > size.y)
			normal.y = Mathf::Sign(diff.y);
		else
			normal.x = Mathf::Sign(diff.x);

		return std::make_pair(bounds, normal);
	}
}
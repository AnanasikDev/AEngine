#include "Collider.h"
#include "CollisionInfo.h"
#include "Vector.h"
#include "Physics.h"
#include "Mathf.h"
#include <iostream>

namespace aengine {
	const float Physics::g = -9.81f;
	const float Physics::airResistance = 0.045f;
	const int Physics::fixedUpdateIntervalMs = 50;

	std::pair<bool, CollisionInfo> Physics::AreOverlapping(const CircleCollider* c1, const CircleCollider* c2) {
		Vectorf delta = (c2->worldCenter - c1->worldCenter);
		float distance = delta.getLength();
		bool areover = distance <= c1->radius + c2->radius;
		CollisionInfo colinfo;
		if (areover) {
			colinfo.normal = delta;
			colinfo.position = (c1->worldCenter + c2->worldCenter) / 2.f;
		}
		return std::make_pair(areover, colinfo);
	}

	std::pair<bool, CollisionInfo> Physics::AreOverlapping(const RectCollider* c1, const CircleCollider* c2) {
		throw std::exception("Non-implemented function Physics::AreOverlapping (2) cannot be invoked.");
		
		return std::make_pair(false, CollisionInfo());
	}

	std::pair<bool, CollisionInfo> Physics::AreOverlapping(const RectCollider* c1, const RectCollider* c2) {
		Vectorf pos;
		Vectorf normal;

		Bounds bounds = Bounds::getIntersectionBounds(c1->bounds, c2->bounds);
		Vectorf diff = c2->worldCenter - c1->worldCenter;
		Vectorf size = bounds.getSize();
		normal = diff;

		//std::cout << c1->bounds << " : " << c2->bounds << std::endl;

		return std::make_pair(!bounds.isEmpty, CollisionInfo(normal, bounds.getCenter()));
	}
}
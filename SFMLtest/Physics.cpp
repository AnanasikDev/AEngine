#include "Collider.h"
#include "RectCollider.h"
#include "CircleCollider.h"
#include "Vector.h"
#include "Mathf.h"
#include "Physics.h"
#include "Line.h"
#include <iostream>

namespace aengine {

	const float Physics::g = -9.81f;
	const float Physics::airResistance = 0.005f;
	const int Physics::fixedUpdateIntervalMs = 20;

	std::pair<Bounds, Vectorf> Physics::getOverlap(const CircleCollider* c1, const CircleCollider* c2) {
		Vectorf delta = (c1->center - c2->center);
		float distance = delta.getLength();
		bool areover = distance < c1->radius + c2->radius;
		if (!areover)
			return std::make_pair(Bounds::empty, Vectorf::zero);
		Bounds bounds;
		// TEMPORARY IMPLEMENTATION
		bounds.setCenterAndSize((c1->center + c2->center) / 2.f, Vectorf::one);
		return std::make_pair(bounds, delta.normalized());
	}

	std::pair<Bounds, Vectorf> Physics::getOverlap(const RectCollider* c1, const CircleCollider* c2) {
	
		bool areOver = false;
		if (c1->bounds.extend(c2->radius, c2->radius, 0, 0).isPointInside(c2->center)) {
			
			areOver = true;
		}

		else if (c1->bounds.extend(0, 0, c2->radius, c2->radius).isPointInside(c2->center)) {
			areOver = true;
		}
		
		else
		{
			for (Vectorf vertex : c1->bounds.getPoints()) {
				float distance = (vertex - c2->center).getLength();
				if (distance < c2->radius)
				{
					areOver = true;
					break;
				}
			}
		}

		if (!areOver)
			return std::pair<Bounds, Vectorf>();

		Bounds bounds;
		bounds.setCenterAndSize(c2->center, Vectorf(c2->radius * 2, c2->radius * 2));
		bounds = Bounds::getIntersectionBounds(bounds, c1->bounds);
		Vectorf diff = c2->center - c1->center;
		Vectorf normal;
		Vectorf size = bounds.getSize();

		if (size.x > size.y)
			normal.y = Mathf::sign(diff.y);
		else
			normal.x = Mathf::sign(diff.x);

		return std::pair<Bounds, Vectorf>(bounds, normal);
	}

	std::pair<Bounds, Vectorf> Physics::getOverlap(const RectCollider* c1, const RectCollider* c2) {
		Vectorf normal;

		Bounds bounds = Bounds::getIntersectionBounds(c1->bounds, c2->bounds);
		Vectorf diff = c1->center - c2->center;
		Vectorf size = bounds.getSize();

		if (size.x > size.y)
			normal.y = Mathf::sign(diff.y);
		else
			normal.x = Mathf::sign(diff.x);

		return std::make_pair(bounds, normal);
	}

	std::vector<Collider*> Physics::segmentCastAll(const Line& line) {
		std::vector<Collider*> results;
		for (Collider* collider : Collider::colliders) {
			if (auto rectCollider = dynamic_cast<RectCollider*>(collider)) {
				if (Line::areSegmentBoundsIntesecting(line, rectCollider->bounds)) {
					results.push_back(collider);
					continue;
				}
			}
			if (auto circleCollider = dynamic_cast<CircleCollider*>(collider)) {
				if (Line::getSegmentCircleIntersection(line, circleCollider->center, circleCollider->radius)) {
					results.push_back(collider);
					continue;
				}
			}
		}
		return results;
	}
}
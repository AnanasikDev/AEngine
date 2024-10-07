#include "Collider.h"
#include "RectCollider.h"
#include "CircleCollider.h"
#include <iostream>
#include "List.h"
#include "Physics.h"
#include "Gameobject.h"
#include <string>

namespace aengine {

	class Gameobject;

	std::vector<Collider*> Collider::colliders;

	Collider::Collider() {
		gameobject = nullptr;
		Collider::colliders.push_back(this);
	}

	Collider::Collider(Gameobject* gameobject) {
		this->gameobject = gameobject;
		Collider::colliders.push_back(this);
	}

	Collider::~Collider() {
		List::remove<Collider*>(Collider::colliders, this);
	}

	bool Collider::isPointInside(Vectorf& point) {

		// Try calculate for circle collider
		auto circleCollider = dynamic_cast<CircleCollider*>(this);
		if (circleCollider != nullptr) {
			return (circleCollider->center - point).getLength() <= circleCollider->radius;
		}
		
		// If failed, try calculate for rect collider
		auto rectCollider = dynamic_cast<RectCollider*>(this);
		if (rectCollider != nullptr) {
			return rectCollider->bounds.isPointInside(point);
		}

		std::cout << "Failed to cast a collider to any of existing types (only circle and rect are supported) got:" << this->toString() << std::endl;

		// If failed, crash with error message
		throw std::exception("Failed to cast a collider to any of existing types (only circle and rect are supported)");
	}

	std::pair<Bounds, Vectorf> Collider::getOverlap(const Collider* other) {
		auto circleCollider1 = dynamic_cast<const CircleCollider*>(this);
		auto rectCollider1 = dynamic_cast<const RectCollider*>(this);

		auto circleCollider2 = dynamic_cast<const CircleCollider*>(other);
		auto rectCollider2 = dynamic_cast<const RectCollider*>(other);

		if (circleCollider1 != nullptr && circleCollider2 != nullptr) {
			return Physics::getOverlap(circleCollider1, circleCollider2);
		}

		if (circleCollider1 != nullptr && rectCollider2 != nullptr) {
			return Physics::getOverlap(rectCollider2, circleCollider1);
		}

		if (rectCollider1 != nullptr && circleCollider2 != nullptr) {
			return Physics::getOverlap(rectCollider1, circleCollider2);
		}

		if (rectCollider1 != nullptr && rectCollider2 != nullptr) {
			return Physics::getOverlap(rectCollider1, rectCollider2);
		}

		throw std::exception("Collider::IsOvelapping cannot handle the given pair of colliders.");

		return std::make_pair(Bounds(), Vectorf());
	}

	void Collider::update(const Vectorf& position) {
		this->center = position;
	}

	std::string Collider::toString() const {
		return "Collider ";
	}
}
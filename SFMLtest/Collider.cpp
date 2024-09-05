#include "Collider.h"
#include <iostream>
#include "List.h"

namespace aengine {

	class Gameobject;

	std::vector<Collider*> Collider::colliders;

	Collider::Collider() {
		gameobject = nullptr;
		Collider::colliders.push_back(this);
	}

	Collider::Collider(Gameobject* gameobject) {
		this->gameobject = gameobject;
		List::Remove<Collider*>(Collider::colliders, this);
	}

	bool Collider::IsPointInside(Vectorf& point) {

		std::cout << "Is point inside call for point " << point.toStr() << std::endl;

		// Try calculate for circle collider
		auto circleCollider = dynamic_cast<CircleCollider*>(this);
		if (circleCollider != nullptr) {
			return (circleCollider->center - point).Magnitude() <= circleCollider->radius;
		}
		
		// If failed, try calculate for rect collider
		auto rectCollider = dynamic_cast<BoxCollider*>(this);
		if (circleCollider != nullptr) {
			return (circleCollider->center - point).Magnitude() <= circleCollider->radius;
		}

		// If failed, crash with error message
		throw std::exception("Failed to cast a collider to any of existing types (only circle and rect are supported");
	}

	bool Collider::IsOverlapping(const Collider& other) {
		auto circleCollider1 = dynamic_cast<CircleCollider*>(this);
		if (circleCollider1 != nullptr) {
		}
	}

	void CircleCollider::SetScale(float scale) {
		this->radius *= scale;
	}

	void BoxCollider::SetScale(float scale) {
		this->size *= scale;
	}

	CircleCollider::CircleCollider() : 
		Collider(), radius(0.f)
	{

	}
	CircleCollider::CircleCollider(Gameobject* gameobject) : 
		Collider(gameobject), radius(0.f)
	{

	}

	BoxCollider::BoxCollider() :
		Collider(), size()
	{

	}
	BoxCollider::BoxCollider(Gameobject* gameobject) :
		Collider(gameobject), size()
	{

	}

	void Collider::Update(const Vectorf& position) {
		this->center = position;
	}
}
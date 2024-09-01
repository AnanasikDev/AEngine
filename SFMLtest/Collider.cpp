#include "Collider.h"
#include <iostream>

namespace aengine {

	class Gameobject;

	Collider::Collider() {
		gameobject = nullptr;
	}

	Collider::Collider(Gameobject* gameobject) {
		this->gameobject = gameobject;
	}

	bool Collider::IsPointInside(Vectorf& point) {

		std::cout << "Is point inside call for point " << point.toStr() << std::endl;

		// Try calculate for circle collider
		auto circleCollider = dynamic_cast<CircleCollider*>(this);
		if (circleCollider != nullptr) {
			return (circleCollider->center - point).Magnitude() <= circleCollider->radius;
		}
		
		// If failed, try calculate for rect collider
		auto rectCollider = dynamic_cast<RectCollider*>(this);
		if (circleCollider != nullptr) {
			return (circleCollider->center - point).Magnitude() <= circleCollider->radius;
		}

		// If failed, crash with error message
		throw std::exception("Failed to cast a collider to any of existing types (only circle and rect are supported");
	}

	void CircleCollider::SetScale(float scale) {
		this->radius *= scale;
	}

	void RectCollider::SetScale(float scale) {
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

	RectCollider::RectCollider() :
		Collider(), size()
	{

	}
	RectCollider::RectCollider(Gameobject* gameobject) :
		Collider(gameobject), size()
	{

	}
}
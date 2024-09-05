#include "Collider.h"
#include <iostream>
#include "List.h"
#include "Physics.h"
#include "CollisionInfo.h"

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
		auto rectCollider = dynamic_cast<RectCollider*>(this);
		if (circleCollider != nullptr) {
			return (circleCollider->center - point).Magnitude() <= circleCollider->radius;
		}

		// If failed, crash with error message
		throw std::exception("Failed to cast a collider to any of existing types (only circle and rect are supported");
	}

	bool Collider::IsOverlapping(const Collider* other) {
		CollisionInfo* info = nullptr;
		auto circleCollider1 = dynamic_cast<const CircleCollider*>(this);
		auto boxCollider1 = dynamic_cast<const CircleCollider*>(this);

		auto circleCollider2 = dynamic_cast<const CircleCollider*>(other);
		auto boxCollider2 = dynamic_cast<const CircleCollider*>(other);

		if (circleCollider1 != nullptr && circleCollider2 != nullptr) {
			return Physics::AreOverlapping(circleCollider1, circleCollider2, info);
		}

		if (circleCollider1 != nullptr && boxCollider2 != nullptr) {
			return Physics::AreOverlapping(circleCollider1, boxCollider2, info);
		}

		if (boxCollider1 != nullptr && circleCollider2 != nullptr) {
			return Physics::AreOverlapping(circleCollider2, boxCollider1, info);
		}

		if (boxCollider1 != nullptr && boxCollider2 != nullptr) {
			return Physics::AreOverlapping(boxCollider1, boxCollider2, info);
		}

		throw std::exception("Collider::IsOvelapping cannot handle the given pair of colliders.");

		return false;
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

	void Collider::Update(const Vectorf& position) {
		this->center = position;
	}
}
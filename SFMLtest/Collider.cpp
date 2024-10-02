#include "Collider.h"
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
		List::Remove<Collider*>(Collider::colliders, this);
	}

	bool Collider::IsPointInside(Vectorf& point) {

		// Try calculate for circle collider
		auto circleCollider = dynamic_cast<CircleCollider*>(this);
		if (circleCollider != nullptr) {
			return (circleCollider->worldCenter - point).getLength() <= circleCollider->radius;
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

	CircleCollider::CircleCollider(Gameobject* gameobject, float radius) :
		Collider(gameobject), radius(radius)
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

	RectCollider::RectCollider(Gameobject* gameobject, Vectorf size) :
		Collider(gameobject), size(size)
	{
		bounds.setCenterAndSize(gameobject->getPosition(), size);
	}

	void Collider::Update(const Vectorf& position) {
		this->worldCenter = position;
	}

	void RectCollider::Update(const Vectorf& position) {
		Collider::Update(position);
		this->bounds.setCenter(position);
	}

	std::string Collider::toString() const {
		return "Collider ";
	}

	std::string RectCollider::toString() const {
		return Collider::toString() + ":Rect";
	}

	std::string CircleCollider::toString() const {
		return Collider::toString() + ":Circle";
	}
}
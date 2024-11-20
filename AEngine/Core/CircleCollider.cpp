#include "CircleCollider.h"

namespace aengine {
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

	void CircleCollider::setScale(float scale) {
		this->radius *= scale;
	}

	bool CircleCollider::isPointInside(const Vectorf& point) const {
		return (center - point).getLength() <= radius;
	}

	std::string CircleCollider::toString() const {
		return Collider::toString() + ":Circle";
	}
}

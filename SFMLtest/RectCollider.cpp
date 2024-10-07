#include "RectCollider.h"
#include "Gameobject.h"

namespace aengine {
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

	void RectCollider::setScale(float scale) {
		this->size *= scale;
	}

	void RectCollider::update(const Vectorf& position) {
		Collider::update(position);
		this->bounds.setCenter(position);
	}

	std::string RectCollider::toString() const {
		return Collider::toString() + ":Rect";
	}
}

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

	bool RectCollider::isPointInside(const Vectorf& point) const {
		return bounds.isPointInside(point);
	}

	Line RectCollider::getIntersection(const Line& line) const {
		
		bool p1inside = isPointInside(line.p1);
		bool p2inside = isPointInside(line.p2);

		// if both ends are inside, return the original line
		if (p1inside && p2inside) {
			return line;
		}

		// if p1 end is inside
		if (p1inside && !p2inside) {
			return Line(line.p1, Vectorf());
		}

		if (!p1inside && p2inside) {

		}

		return Line(Vectorf(), Vectorf());
	}
}

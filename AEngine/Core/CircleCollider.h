#pragma once

#include "Collider.h"

namespace aengine {
	struct CircleCollider : public Collider {
		float radius;

		CircleCollider();
		CircleCollider(Gameobject* gameobject);
		CircleCollider(Gameobject* gameobject, float radius);
		~CircleCollider() = default;

		void setScale(float scale) override;
		bool isPointInside(const Vectorf& point) const override;
		Line getIntersection(const Line& line) const override;

		std::string toString() const override;
	};
}

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
		std::string toString() const override;
	};
}

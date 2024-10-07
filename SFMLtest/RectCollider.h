#pragma once

#include "Collider.h"

namespace aengine {
	struct RectCollider : public Collider {
		Vectorf size;
		Bounds bounds;

		RectCollider();
		RectCollider(Gameobject* gameobject);
		RectCollider(Gameobject* gameobject, Vectorf size);
		~RectCollider() = default;

		void setScale(float scale) override;
		void update(const Vectorf&) override;
		std::string toString() const override;
	};
}

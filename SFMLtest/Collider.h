#pragma once

#include <SFML/Graphics.hpp>
#include "Vector.h"

namespace aengine {

	struct Collider {
		class Gameobject* gameobject;

		Vectorf center;

		Collider();
		Collider(Gameobject* gameobject);
		~Collider() = default;

		void Update(const Vectorf& position);

		virtual bool IsPointInside(Vectorf& point);
		virtual void SetScale(float scale) = 0;
	};


	struct CircleCollider : public Collider {
		float radius;

		CircleCollider();
		CircleCollider(Gameobject* gameobject);
		~CircleCollider() = default;

		void SetScale(float scale) override;
	};

	struct RectCollider : public Collider {
		Vectorf size;

		RectCollider();
		RectCollider(Gameobject* gameobject);
		~RectCollider() = default;

		void SetScale(float scale) override;
	};
}
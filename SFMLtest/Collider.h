#pragma once

#include <SFML/Graphics.hpp>
#include "Vector.h"
#include <vector>

namespace aengine {

	struct Collider {
		class Gameobject* gameobject;

		static std::vector<Collider*> colliders;

		Vectorf center;

		Collider();
		Collider(Gameobject* gameobject);
		~Collider();

		void Update(const Vectorf& position);

		virtual bool IsPointInside(Vectorf& point);
		virtual bool IsOverlapping(const Collider* other);
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
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

		/// <summary>
		/// Detects whether the given point is
		/// inside or outside of the collider.
		/// </summary>
		virtual bool IsPointInside(Vectorf& point);

		/// <summary>
		/// Detects collision between the pair
		/// of colliders (this and other). Dynamic_cast's
		/// both to detect collision between any types
		/// of colliders.
		/// </summary>
		virtual bool IsOverlapping(const Collider* other);

		/// <summary>
		/// Multiplies size of the collider by given factor.
		/// </summary>
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

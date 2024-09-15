#pragma once

#include <SFML/Graphics.hpp>
#include "Vector.h"
#include <vector>
#include "Bounds.h"
#include <string>

namespace aengine {

	class Gameobject;

	struct Collider {
		Gameobject* gameobject;

		static std::vector<Collider*> colliders;

		Vectorf worldCenter;

		Collider();
		Collider(Gameobject* gameobject);
		~Collider();

		virtual void Update(const Vectorf& position);

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
		virtual Bounds IsOverlapping(const Collider* other);

		/// <summary>
		/// Multiplies size of the collider by given factor.
		/// </summary>
		virtual void SetScale(float scale) = 0;

		virtual std::string toString() const;
	};


	struct CircleCollider : public Collider {
		float radius;

		CircleCollider();
		CircleCollider(Gameobject* gameobject);
		~CircleCollider() = default;

		void SetScale(float scale) override;
		std::string toString() const override;
	};

	struct RectCollider : public Collider {
		Vectorf size;
		Bounds bounds;

		RectCollider();
		RectCollider(Gameobject* gameobject);
		RectCollider(Gameobject* gameobject, Vectorf size);
		~RectCollider() = default;

		void SetScale(float scale) override;
		void Update(const Vectorf&) override;
		std::string toString() const override;
	};
}

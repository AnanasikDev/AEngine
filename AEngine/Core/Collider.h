#pragma once

#include "SFML/Graphics.hpp"
#include "Vector.h"
#include <vector>
#include "Bounds.h"
#include <string>
#include "Mathf.h"
#include "Line.h"

namespace aengine {

	class Gameobject;

	struct Collider {
		Gameobject* gameobject;

		static std::vector<Collider*> colliders;

		/// <summary>
		/// If true, collisions are calculated but it doesn't affect objects's position or velocity
		/// </summary>
		bool isTrigger = false;

		Vectorf center;

		Collider();
		Collider(Gameobject* gameobject);
		~Collider();

		virtual void update(const Vectorf& position);

		/// <summary>
		/// Detects whether the given point is
		/// inside or outside of the collider.
		/// </summary>
		virtual bool isPointInside(const Vectorf& point) const;

		/// <summary>
		/// Detects collision between the pair
		/// of colliders (this and other). Dynamic_cast's
		/// both to detect collision between any types
		/// of colliders.
		/// </summary>
		/// <returns>
		/// Returns Bounds of intersection (overlap) and normal as Vectorf
		/// </returns>
		virtual std::pair<Bounds, Vectorf> getOverlap(const Collider* other);

		/// <summary>
		/// Multiplies size of the collider by given factor.
		/// </summary>
		virtual void setScale(float scale) = 0;

		virtual std::string toString() const;
	};
}

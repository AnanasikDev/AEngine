#pragma once

#include "Vector.h"

namespace aengine {
	class Rigidbody {
	private:
		Vectorf fvelocity;
		Vectorf position;
		class Gameobject* gameobject;

		float g;
		float airResistance;
		float mass;
		Vectorf facceleration;

	public:
		
		bool useGravity = true;

		Rigidbody();
		Rigidbody(Gameobject* gameobject);
		~Rigidbody() = default;

		Vectorf getVelocity() const;
		Vectorf getPosition() const;
		void setPosition(Vectorf pos);

		/// <summary>
		/// Applies forces, computes collisions, 
		/// updates gameobject position
		/// </summary>
		void FixedUpdate();

		/// <summary>
		/// Calculates and applies intermediate positions
		/// </summary>
		void Update();

		void AddForce(Vectorf force);

		void CheckCollisions();
	};
}

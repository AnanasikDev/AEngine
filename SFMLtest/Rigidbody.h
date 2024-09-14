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

		float bounciness;
		float stickiness;

	public:
		
		bool useGravity = true;

		Rigidbody();
		Rigidbody(Gameobject* gameobject);
		~Rigidbody() = default;

		Vectorf getVelocity() const;
		Vectorf getFrameVelocity() const;

		Vectorf getPosition() const;
		void setPosition(Vectorf value);

		float getBounciness() const;
		void setBounciness(float value);

		float getStickiness() const;
		void setStickiness(float value);

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

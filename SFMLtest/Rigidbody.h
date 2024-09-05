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

		Vectorf getVelocity() const;
		Vectorf getPosition() const;

		/*  Applies forces,
			calculates collisions,
			updates gameobject position
		*/
		void Update();

		void AddForce(Vectorf force);

		void CheckCollisions();
	};
}

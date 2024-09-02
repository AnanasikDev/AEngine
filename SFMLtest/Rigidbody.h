#pragma once

#include "Vector.h"

namespace aengine {
	class Rigidbody {
	private:
		Vectorf velocity;
		Vectorf position;
		class Gameobject* gameobject;

		float g;
		float airResistance;
		float mass;
		Vectorf acceleration;

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
	};
}

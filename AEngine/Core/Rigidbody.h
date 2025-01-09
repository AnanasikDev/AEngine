#pragma once

#include "Vector.h"
#include "Bounds.h"

namespace aengine {

	struct Collider;

	class Rigidbody {
	private:
		Vectorf velocity;
		class Gameobject* gameobject;

		float g;
		float airResistance;
		float mass;

	public:
		bool useGravity = true;

		/// <summary>
		/// If true, receives forces from objects when collided
		/// </summary>
		bool respondToImpulse = true;

		Rigidbody(Gameobject* gameobject);
		~Rigidbody() = default;

		Vectorf getVelocity() const;
		Vectorf getFrameVelocity() const;
		
		/// <summary>
		/// Overwrites current velocity with a new value, without changing acceleration.
		/// </summary>
		void setVelocity(Vectorf val);

		float getMass() const;
		void setMass(float value);

		/// <summary>
		/// Preset for respondToImpulse and useGravity fields. No response to impulse and no use of gravity
		/// </summary>
		void makeStatic();

		/// <summary>
		/// Preset for respondToImpulse and useGravity fields. Response to impulse and no use of gravity
		/// </summary>
		void makeKinematic();

		/// <summary>
		/// Preset for respondToImpulse and useGravity fields. Response to impulse and use of gravity
		/// </summary>
		void makeDynamic();

		/// <summary>
		/// Applies forces, computes collisions, 
		/// updates gameobject position
		/// </summary>
		void fixedUpdate();

		/// <summary>
		/// Calculates and applies intermediate positions
		/// </summary>
		void update();

		void addForce(Vectorf force);

		void checkCollisions();
		void onCollision(const Bounds& bounds, Vectorf normal, Vectorf velocity, Collider* other);
	};
}

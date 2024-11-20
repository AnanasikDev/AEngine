#pragma once

#include "Vector.h"
#include "Bounds.h"

namespace aengine {

	class Collider;

	class Rigidbody {
	private:
		Vectorf fvelocity;
		class Gameobject* gameobject;

		float g;
		float airResistance;
		float mass;
		Vectorf facceleration;

		float bounciness;
		float stickiness;

	public:

		/// <summary>
		/// If true, it calculates all collisions and detections but does not collide (can overlap, cannot respond to impulses)
		/// </summary>
		bool isTrigger = false;

		bool useGravity = true;

		/// <summary>
		/// If true, receives forces from objects when collided
		/// </summary>
		bool respondToImpulse = true;

		Action<Collider*> onCollisionEvent;

		Rigidbody();
		Rigidbody(Gameobject* gameobject);
		~Rigidbody() = default;

		Vectorf getVelocity() const;
		Vectorf getFrameVelocity() const;

		float getBounciness() const;
		void setBounciness(float value);

		float getStickiness() const;
		void setStickiness(float value);

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

#include "Rigidbody.h"
#include "Collider.h"
#include "Physics.h"
#include "Gameobject.h"
#include <iostream>
#include "Time.h"
#include "Mathf.h"

namespace aengine {

	Rigidbody::Rigidbody() {
		g = Physics::g;
		airResistance = Physics::airResistance;
		mass = 1.f;
		bounciness = 0.8f;
		stickiness = 2.f;
		facceleration = Vectorf();
		this->gameobject = nullptr;
	}

	Rigidbody::Rigidbody(Gameobject* gameobject){
		g = Physics::g;
		airResistance = Physics::airResistance;
		mass = 1.f;
		bounciness = 0.8f;
		stickiness = 2.f;
		facceleration = Vectorf();
		this->gameobject = gameobject;
	}

	Vectorf Rigidbody::getVelocity() const {
		return this->fvelocity;
	}

	Vectorf Rigidbody::getFrameVelocity() const {
		return fvelocity / Time::getDeltaTime();
	}

	float Rigidbody::getBounciness() const {
		return this->bounciness;
	}

	void Rigidbody::setBounciness(float value) {
		this->bounciness = value;
	}

	float Rigidbody::getStickiness() const {
		return this->stickiness;
	}

	void Rigidbody::setStickiness(float value) {
		this->stickiness = value;
	}

	float Rigidbody::getMass() const {
		return this->mass;
	}
	void Rigidbody::setMass(float value) {
		this->mass = value;
	}

	void Rigidbody::addForce(Vectorf force) {
		// may be enforced to not be able to add force to static rigidbodies
		this->fvelocity += force;
	}

	void Rigidbody::fixedUpdate() {

		/*
			Heavy physics computations done in FixedUpdate
			to achieve better performance
		*/

		if (useGravity)
			fvelocity += Vectorf::up * this->g;

		this->fvelocity = this->fvelocity * (1 - Physics::airResistance);

		checkCollisions();

	}

	void Rigidbody::update() {

		/*
			Light computations for seamless updates,
			such as transformations
		*/

		this->gameobject->translate(this->fvelocity * Time::getDeltaTime());
	}

	void Rigidbody::checkCollisions() {
		for (Collider* other : Collider::colliders) {
			
			// no self collisions
			if (this->gameobject->collider.get() == other) continue;

			std::pair<Bounds, Vectorf> overlap = this->gameobject->collider->getOverlap(other);

			Bounds bounds = overlap.first;
			Vectorf normal = overlap.second;

			if (bounds.isEmpty()) continue;

			// collision detected

			auto otherRigidbody = other->gameobject->rigidbody.get();

			if (this->gameobject->collider->isTrigger || other->isTrigger) {
				onCollisionEvent.Invoke(other);
				if (otherRigidbody != nullptr) 
					otherRigidbody->onCollisionEvent.Invoke(this->gameobject->collider.get());
				return; // if any object is trigger, no further calculations needed
			}

			Vectorf size = bounds.getSize();
			
			if (respondToImpulse)
				gameobject->translate(normal * (bounds.getSize() + Vectorf::one * 3));

			if (otherRigidbody != nullptr) {
				
				Vectorf vel = fvelocity;

				Vectorf v1 = fvelocity;
				Vectorf v2 = otherRigidbody->fvelocity;
				float m1 = mass;
				float m2 = otherRigidbody->mass;

				Vectorf impulse1;
				if (otherRigidbody->respondToImpulse) {
					impulse1 = v1 * (m1 - m2) / (m1 + m2) + v2 * (2 * m2) / (m1 + m2);
				}
				else {
					impulse1 = v1;
					if (normal.x == 0)
						impulse1.y = -impulse1.y;
					else if (normal.y == 0)
						impulse1.x = -impulse1.x;
				}

				onCollision(bounds, normal, impulse1, other);

				// Add force to the other object of collision, with regard of velocity 

				Vectorf impulse2 = v1 * (2 * m1) / (m1 + m2) + v2 * (m2 - m1) / (m1 + m2);

				otherRigidbody->onCollision(bounds, -normal, impulse2, this->gameobject->collider.get());
			}
			else {
				onCollision(bounds, normal, fvelocity, other);
			}

			if (getFrameVelocity().getLength() < stickiness) {
				//fvelocity = Vectorf::zero;
			}
		}
	}

	void Rigidbody::onCollision(const Bounds& bounds, Vectorf normal, Vectorf velocity, Collider* other) {
		onCollisionEvent.Invoke(other);

		if (!respondToImpulse) return;

		/*if (normal.x == 0)
			velocity.y = -velocity.y;
		else if (normal.y == 0)
			velocity.x = -velocity.x;*/

		this->fvelocity = velocity * bounciness;
	}

	
	void Rigidbody::makeDynamic() {
		this->respondToImpulse = true;
		this->useGravity = true;
	}

	void Rigidbody::makeKinematic() {
		this->respondToImpulse = true;
		this->useGravity = false;
	}

	void Rigidbody::makeStatic() {
		this->respondToImpulse = false;
		this->useGravity = false;
	}
}

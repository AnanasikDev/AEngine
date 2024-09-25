#include "Rigidbody.h"
#include "Physics.h"
#include "Game.h"
#include "Collider.h"
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
		this->position = gameobject->getPosition();
	}

	Vectorf Rigidbody::getVelocity() const {
		return this->fvelocity;
	}

	Vectorf Rigidbody::getFrameVelocity() const {
		return fvelocity / 1000. * Time::getDeltaTimeMs();
	}

	float Rigidbody::getBounciness() const {
		return this->bounciness;
	}

	void Rigidbody::setBounciness(float value) {
		this->bounciness = value;
	}

	Vectorf Rigidbody::getPosition() const {
		return this->position;
	}

	void Rigidbody::setPosition(Vectorf value) {
		this->position = value;
	}

	float Rigidbody::getStickiness() const {
		return this->stickiness;
	}

	void Rigidbody::setStickiness(float value) {
		this->stickiness = value;
	}

	void Rigidbody::AddForce(Vectorf force) {
		// may be enforced to not be able to add force to static rigidbodies
		this->fvelocity += force;
	}

	void Rigidbody::FixedUpdate() {

		/*
			Heavy physics computations done in FixedUpdate
			to achieve better performance
		*/

		if (useGravity)
			fvelocity += Vectorf::up * this->g;

		this->fvelocity = this->fvelocity * (1 - Physics::airResistance);

		CheckCollisions();

	}

	void Rigidbody::Update() {

		/*
			Light computations for seamless updates,
			such as transformations
		*/

		this->position += (this->fvelocity * Time::getDeltaTimeMs() / 1000.f);
	}

	void Rigidbody::CheckCollisions() {
		for (Collider* other : Collider::colliders) {
			
			// no self collisions
			if (this->gameobject->collider == other) continue;

			std::pair<Bounds, Vectorf> overlap = this->gameobject->collider->getOverlap(other);

			Bounds bounds = overlap.first;
			Vectorf normal = overlap.second;

			if (bounds.isEmpty()) continue;

			// collision detected

			Vectorf size = bounds.getSize();
			
			if (respondToImpulse)
				setPosition(getPosition() + normal * (bounds.getSize() + Vectorf::one * 3));

			auto otherRigidbody = other->gameobject->rigidbody;
			if (otherRigidbody != nullptr) {
				
				Vectorf vel = fvelocity;

				OnCollision(bounds, normal, vel); // - otherRigidbody->fvelocity

				// Add force to the other object of collision, with regard of velocity and mass of this object
				otherRigidbody->OnCollision(bounds, -normal, otherRigidbody->fvelocity);
			}
			else {
				OnCollision(bounds, normal, fvelocity);
			}

			std::cout << gameobject->name << " collided with " << other->gameobject->name << std::endl;

			if (getFrameVelocity().getLength() < stickiness) {
				//fvelocity = Vectorf::zero;
			}
		}
	}

	void Rigidbody::OnCollision(const Bounds& bounds, Vectorf normal, Vectorf velocity) {
		
		if (!respondToImpulse) return;

		if (normal.x == 0)
			velocity.y = -velocity.y;
		else if (normal.y == 0)
			velocity.x = -velocity.x;

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

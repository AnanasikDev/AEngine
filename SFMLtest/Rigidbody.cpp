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

		this->gameobject->Translate(this->fvelocity * Time::getDeltaTime());
	}

	void Rigidbody::CheckCollisions() {
		for (Collider* other : Collider::colliders) {
			
			// no self collisions
			if (this->gameobject->collider == other) continue;

			std::pair<Bounds, Vectorf> overlap = this->gameobject->collider->getOverlap(other);

			Bounds bounds = overlap.first;
			Vectorf normal = overlap.second;

			if (bounds.isEmpty()) continue;

			//std::cout << gameobject->name << " " << bounds << std::endl;

			// collision detected

			Vectorf size = bounds.getSize();
			
			if (respondToImpulse)
				gameobject->Translate(normal * (bounds.getSize() + Vectorf::one * 3));

			auto otherRigidbody = other->gameobject->rigidbody;
			if (otherRigidbody != nullptr) {
				
				Vectorf vel = fvelocity;

				Vectorf v1 = fvelocity;
				Vectorf v2 = otherRigidbody->fvelocity;
				float m1 = mass;
				float m2 = otherRigidbody->mass;

				//Vectorf impulse = vel * mass / otherRigidbody->mass;
				Vectorf impulse1 = v1 * (m1 - m2) / (m1 + m2) + v2 * (2 * m2) / (m1 + m2); //(fvelocity + otherRigidbody->fvelocity) * (otherRigidbody->mass / mass);

				OnCollision(bounds, normal, impulse1); // - otherRigidbody->fvelocity

				// Add force to the other object of collision, with regard of velocity and mass of this object
				//Vectorf impulse2 = otherRigidbody->fvelocity * otherRigidbody->mass / mass;
				//Vectorf impulse2 = (otherRigidbody->fvelocity + fvelocity) * (mass / otherRigidbody->mass);

				Vectorf impulse2 = v1 * (2 * m1) / (m1 + m2) + v2 * (m2 - m1) / (m1 + m2);

				std::cout << "impulse 1: " << impulse1 << " | impulse 2: " << impulse2 << "m1 = " << mass << " m2 = " << otherRigidbody-> mass << std::endl;

				otherRigidbody->OnCollision(bounds, -normal, impulse2);
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

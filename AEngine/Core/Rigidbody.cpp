#include "Rigidbody.h"
#include "Collider.h"
#include "Physics.h"
#include "Gameobject.h"
#include <iostream>
#include "Time.h"
#include "Mathf.h"

namespace aengine {

	Rigidbody::Rigidbody(Gameobject* gameobject){
		g = Physics::g;
		airResistance = Physics::airResistance;
		mass = 1.f;
		this->gameobject = gameobject;
	}

	Vectorf Rigidbody::getVelocity() const {
		return this->fvelocity;
	}

	Vectorf Rigidbody::getFrameVelocity() const {
		return fvelocity / Time::getDeltaTime();
	}

	float Rigidbody::getMass() const {
		return this->mass;
	}
	void Rigidbody::setMass(float value) {
		this->mass = value;
	}

	void Rigidbody::setVelocity(Vectorf value) {
		this->fvelocity = value;
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
		Collider* thisCol = this->gameobject->collider.get();

		for (Collider* otherCol : Collider::colliders) {
			
			// no self collisions
			if (thisCol == otherCol) continue;

			std::pair<Bounds, Vectorf> overlap = thisCol->getOverlap(otherCol);

			Bounds bounds = overlap.first;
			Vectorf normal = overlap.second;

			if (bounds.isEmpty()) continue;

			// collision detected

			auto otherRigidbody = otherCol->gameobject->rigidbody.get();

			if (thisCol->isTrigger || otherCol->isTrigger) {
				std::cout << this->gameobject->name << " triggered with " << otherCol->gameobject->name << std::endl;
				thisCol->onTriggerEvent.Invoke(otherCol);
				otherCol->onTriggerEvent.Invoke(thisCol);
				return; 
				// if any object is trigger, no further calculations needed
			}

			thisCol->onBeforeCollisionEvent.Invoke(otherCol);
			otherCol->onBeforeCollisionEvent.Invoke(thisCol);

			std::cout << this->gameobject->name << " collided with " << otherCol->gameobject->name << std::endl;

			Vectorf size = bounds.getSize();
			
			if (respondToImpulse)
				gameobject->translate(normal * (bounds.getSize() + Vectorf::one * 3));

			if (otherRigidbody != nullptr && otherRigidbody->respondToImpulse) {

				Vectorf v1 = fvelocity;
				Vectorf v2 = otherRigidbody->fvelocity;
				float m1 = mass;
				float m2 = otherRigidbody->mass;

				Vectorf impulse1 = v1 * (m1 - m2) / (m1 + m2) + v2 * (2 * m2) / (m1 + m2);
				onCollision(bounds, normal, impulse1, otherCol);

				Vectorf impulse2 = v1 * (2 * m1) / (m1 + m2) + v2 * (m2 - m1) / (m1 + m2);
				otherRigidbody->onCollision(bounds, -normal, impulse2, thisCol);
			}
			else if (respondToImpulse)
			{
				Vectorf impulse1 = fvelocity - normal * fvelocity.dotProduct(normal) * 2;

				onCollision(bounds, normal, impulse1, otherCol);
			}

			if (getFrameVelocity().getLength() < this->gameobject->collider->stickiness * otherCol->stickiness) {
				//fvelocity = Vectorf::zero;
			}

			thisCol->onAfterCollisionEvent.Invoke(otherCol);
			otherCol->onAfterCollisionEvent.Invoke(thisCol);
		}
	}

	void Rigidbody::onCollision(const Bounds& bounds, Vectorf normal, Vectorf velocity, Collider* other) {
		fvelocity = velocity * gameobject->collider->bounciness * other->bounciness;
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

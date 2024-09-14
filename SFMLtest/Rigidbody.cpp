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
		this->fvelocity += force;
	}

	void Rigidbody::FixedUpdate() {

		/*
			Heavy physics computations done in FixedUpdate
			to achieve better performance
		*/

		this->fvelocity += 
			Vectorf::up * this->g;

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
			
			if (this->gameobject->collider == other) continue;

			auto overlap = other->IsOverlapping(this->gameobject->collider);
			if (!overlap.isEmpty()) {
				// collision detected
				Vectorf vec;
				Vectorf size = overlap.getSize();
				if (size.x > size.y)
					vec.y = -Mathf::Sign(fvelocity.y);
				else
					vec.x = -Mathf::Sign(fvelocity.x);
				setPosition(getPosition() + vec * overlap.getSize() + Vectorf::up*3);
				//std::cout << "Collision detected at: " << this->gameobject->name << " " << other->gameobject->name << std::endl;
				std::cout << getFrameVelocity() << std::endl;
				if (getFrameVelocity().getLength() < stickiness)
					fvelocity = Vectorf::zero;
				else
					AddForce(fvelocity * -1.f + fvelocity * -1.f * bounciness);
			}
		}
	}
}

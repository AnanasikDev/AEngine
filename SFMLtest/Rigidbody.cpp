#include "Rigidbody.h"
#include "Physics.h"
#include "Game.h"
#include "Collider.h"
#include "Gameobject.h"
#include <iostream>
#include "Time.h"

namespace aengine {

	Rigidbody::Rigidbody() {
		g = Physics::g;
		airResistance = Physics::airResistance;
		mass = 1.f;
		facceleration = Vectorf();
		this->gameobject = nullptr;
	}

	Rigidbody::Rigidbody(Gameobject* gameobject){
		g = Physics::g;
		airResistance = Physics::airResistance;
		mass = 1.f;
		facceleration = Vectorf();
		this->gameobject = gameobject;
	}

	Vectorf Rigidbody::getVelocity() const {
		return this->fvelocity;
	}

	Vectorf Rigidbody::getPosition() const {
		return this->position;
	}

	void Rigidbody::setPosition(Vectorf pos) {
		this->position = pos;
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
			if (this->gameobject->collider != other && other->IsOverlapping(this->gameobject->collider)) {
				// collision detected
				std::cout << "Collision detected at: " << this->gameobject->getPosition().toStr() << " : " << other->gameobject->getPosition().toStr() << " " << this << " : " << other << std::endl;
			}
		}
	}
}

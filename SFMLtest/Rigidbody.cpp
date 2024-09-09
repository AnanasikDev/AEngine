#include "Rigidbody.h"
#include "Physics.h"
#include "Game.h"
#include "Collider.h"
#include "Gameobject.h"
#include <iostream>

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

	void Rigidbody::AddForce(Vectorf force) {
		this->fvelocity += force;
	}

	void Rigidbody::FixedUpdate() {

		this->fvelocity += this->facceleration + 
			Vectorf::up * this->g;
		this->position += this->fvelocity;

		CheckCollisions();
	}

	void Rigidbody::Update() {
		
	}

	void Rigidbody::CheckCollisions() {
		for (Collider* other : Collider::colliders) {
			if (other->IsOverlapping(this->gameobject->collider)) {
				// collision detected
				std::cout << "Collision detected!" << std::endl;
			}
		}
	}
}

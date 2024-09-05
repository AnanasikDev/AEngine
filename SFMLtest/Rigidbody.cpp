#include "Rigidbody.h"
#include "Physics.h"
#include "Game.h"

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

	void Rigidbody::Update() {

		this->fvelocity += this->facceleration + 
			Vectorf::up * this->g;
		this->position += this->fvelocity;
	}

	void Rigidbody::CheckCollisions() {
	}
}

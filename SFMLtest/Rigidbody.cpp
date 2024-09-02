#include "Rigidbody.h"
#include "Physics.h"

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
		return this->velocity;
	}

	Vectorf Rigidbody::getPosition() const {
		return this->position;
	}

	void Rigidbody::AddForce(Vectorf force) {
		this->velocity += force;
	}

	void Rigidbody::Update() {

		this->velocity += this->facceleration + Vectorf::up * this->g;
		this->position += this->velocity;
	}
}

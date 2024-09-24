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

		//this->fvelocity = this->fvelocity * (1 - Physics::airResistance) + Vectorf::up * this->g;

		this->fvelocity = (this->fvelocity + Vectorf::up * this->g) * (1 - Physics::airResistance);


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
			setPosition(getPosition() + normal * (bounds.getSize() + Vectorf::one * 3));
			if (getFrameVelocity().getLength() < stickiness) {
				fvelocity = Vectorf::zero;
			}
			else
			{
				Vectorf f = fvelocity;
				if (normal.x == 0)
					f.y = -f.y;
				else if (normal.y == 0)
					f.x = -f.x;

				this->fvelocity = f * bounciness;

				// Add force to the other object of collision, with regard of velocity and mass of this object
				//AddForce(f * (1 + bounciness));
			}
		}
	}
}

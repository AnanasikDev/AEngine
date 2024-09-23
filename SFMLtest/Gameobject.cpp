#include "Gameobject.h"
#include "Renderer.h"
#include "Collider.h"
#include "Rigidbody.h"
#include <iostream>
#include "Game.h"
#include "List.h"
#include "Vector.h"

namespace aengine {

	Gameobject::Gameobject() {
		position = Vectorf(0, 0);
		name = "";
		Register();
	}

	Gameobject::Gameobject(std::string name) {
		this->name = name;
		this->position = Vectorf(0, 0);
		Register();
	}

	Gameobject::Gameobject(std::string name, Renderer* renderer) {
		this->name = name;
		this->position = Vectorf(0, 0);
		this->renderer = renderer;
		Register();
	}

	Gameobject::Gameobject(std::string name, Renderer* renderer, Collider* collider, Rigidbody* rigidbody) {
		this->name = name;
		this->position = Vectorf(0, 0);
		this->renderer = renderer;
		this->collider = collider;
		this->rigidbody = rigidbody;
		Register();
	}

	Gameobject::Gameobject(const Gameobject& other) {
		this->position = other.position;
		this->name = other.name;
		Register();
	}

	Gameobject::~Gameobject() {
		if (renderer != nullptr) delete renderer;
		if (collider != nullptr) delete collider;
		if (rigidbody != nullptr) delete rigidbody;

		List::Remove<Gameobject*>(aengine::Game::instance->gameobjects, this);
	}

	void Gameobject::Render() {
		if (renderer != nullptr)
			renderer->Render();
	}

	void Gameobject::Update() {

		// if rigidbody is applied, it takes control over GO's position
		if (rigidbody != nullptr) {
			this->position = rigidbody->getPosition();
			rigidbody->Update();
		}
		
		if (collider != nullptr) {
			collider->Update(this->position);
		}
		
		if (renderer != nullptr) {
			renderer->Update(this->position);
		}
	}

	void Gameobject::Register() {
		aengine::Game::instance->gameobjects.push_back(this);
	}

	void Gameobject::Start() {

	}

	void Gameobject::SetScale(float scale) {
		if (renderer != nullptr) renderer->SetScale(scale);
		if (collider != nullptr) collider->SetScale(scale);
	}

	void Gameobject::SetPosition(Vectorf pos) {
		position = pos;
		if (rigidbody != nullptr) {
			rigidbody->setPosition(pos);
		}
	}

	void Gameobject::SetPosition(float x, float y) {
		SetPosition(Vectorf(x, y));
	}

	Vectorf Gameobject::getPosition() const {
		return this->position;
	}

	void Gameobject::Translate(Vectorf delta) {
		position += delta;
	}

	void Gameobject::Translate(float dx, float dy) {
		Translate(Vectorf(dx, dy));
	}

	Gameobject* Gameobject::getGameobject() {
		return this;
	}
}
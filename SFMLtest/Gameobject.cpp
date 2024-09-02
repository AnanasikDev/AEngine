#include "Gameobject.h"
#include "Renderer.h"
#include "Collider.h"
#include "Rigidbody.h"
#include <iostream>
#include "Game.h"

namespace aengine {
	Gameobject::Gameobject(std::string name) {
		this->name = name;
		this->position = Vectorf(0, 0);
	}

	void Gameobject::Render() {
		if (renderer != nullptr)
			renderer->Render();
	}

	void Gameobject::Update() {
		if (collider != nullptr) {
			collider->Update(this->position);
		}
		if (renderer != nullptr) {
			renderer->Update(this->position);
		}
		if (rigidbody != nullptr) {
			rigidbody->Update(this->position);
		}
	}

	void Gameobject::Init() {
		aengine::Game::instance->gameobjects.push_back(this);
	}

	Gameobject::~Gameobject() {
		if (renderer != nullptr) delete renderer;
		if (collider != nullptr) delete collider;
		if (rigidbody != nullptr) delete rigidbody;

		auto it = std::find(aengine::Game::instance->gameobjects.begin(), aengine::Game::instance->gameobjects.end(), this);

		// If element is found found, erase it 
		if (it != aengine::Game::instance->gameobjects.end()) {
			aengine::Game::instance->gameobjects.erase(it);
		}
	}

	void Gameobject::SetScale(float scale) {
		if (renderer != nullptr) renderer->SetScale(scale);
		if (collider != nullptr) collider->SetScale(scale);
	}
}
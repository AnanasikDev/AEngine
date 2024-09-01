#include "Gameobject.h"
#include "Renderer.h"
#include "Collider.h"
#include <iostream>

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
			collider->center = this->position;
		}
		if (renderer != nullptr)
			renderer->Update(this->position);
	}

	void Gameobject::Init() {

	}

	void Gameobject::SetScale(float scale) {
		if (renderer != nullptr) renderer->SetScale(scale);
		if (collider != nullptr) collider->SetScale(scale);
	}
}
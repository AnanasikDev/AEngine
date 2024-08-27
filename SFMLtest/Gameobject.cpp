#include "Gameobject.h"
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
		if (renderer != nullptr)
			renderer->Update();
	}

	void Gameobject::Init() {

	}
}
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
		std::cout << "Gameobject update" << std::endl;
		if (renderer != nullptr)
			renderer->Update();
	}

	void Gameobject::Init() {

	}
}
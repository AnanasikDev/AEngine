#include "Gameobject.h"
#include <iostream>

Gameobject::Gameobject(std::string name) {
	this->name = name;
	this->position = Vectorf(0, 0);
	//Init();
}

void Gameobject::Render() {
	if (renderer != nullptr)
		renderer->Render();
}

void Gameobject::Update() {
	if (renderer != nullptr)
		renderer->Update();
}

std::shared_ptr<Component> Gameobject::GetComponent(Component component) {
	for (auto c : this->components)
		if (&(*c) == &component)
			return c;
	return nullptr;
}

void Gameobject::AddComponent(Component component) {
	this->components.push_back(std::make_shared<Component>(component));
}
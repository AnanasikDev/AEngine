#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Vector.h"
#include "Collider.h"
#include "Renderer.h"

class Gameobject {
private:
	std::vector<std::shared_ptr<Component>> components;

public:
	Vectorf position;
	std::string name;

	std::unique_ptr<Collider> collider;
	std::unique_ptr<Renderer> renderer;

	Gameobject(std::string name);
	~Gameobject() = default;

	virtual void Init() = 0;

	virtual void Render() = 0;
	virtual void Update() = 0;
	
	std::shared_ptr<Component> GetComponent(Component& component);

	void AddComponent(Component& component);
};
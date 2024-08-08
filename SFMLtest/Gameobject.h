#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Vector.h"

class Gameobject {

private:
public:
	Vectorf position;
	std::string name;

	Gameobject(std::string name);
	~Gameobject() = default;

	virtual void Init() = 0;

	virtual void Render() = 0;
	virtual void Update() = 0;
};
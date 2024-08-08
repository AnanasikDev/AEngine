#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Gameobject {

private:
public:
	sf::Vector2f position;
	std::string name;

	Gameobject(std::string name);
	~Gameobject() = default;

	virtual void Init() = 0;

	virtual void Render() = 0;
	virtual void Update() = 0;
};
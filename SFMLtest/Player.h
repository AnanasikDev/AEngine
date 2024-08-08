#pragma once

#include "Game.h"
#include "Gameobject.h"

class Player : public Gameobject {
private:


public:
	sf::RectangleShape rect;

	using Gameobject::Gameobject;

	void Init() override;
	void Update() override;
	void Render() override;
};
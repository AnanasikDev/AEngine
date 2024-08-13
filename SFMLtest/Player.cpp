#include "Player.h"
#include "Gameobject.h"
#include <iostream>

void Player::Init() {
	auto sh = new ShapeRenderer(*this, *Game::instance->getWindow());
	auto circle = new sf::CircleShape(30);
	circle->setRadius(30);
	circle->setFillColor(sf::Color(255, 100, 10));
	circle->setPosition(position.getsf());
	renderer = std::make_unique<ShapeRenderer>(sh);
	position = Vectorf(40, 50);
}

void Player::Update() {
	this->position += Vectorf(1, 2);
	renderer->Update();
}

void Player::Render() {
	Gameobject::Render();
}
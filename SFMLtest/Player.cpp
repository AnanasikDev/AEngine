#include "Player.h"
#include "Gameobject.h"
#include <iostream>

void Player::Init() {
	rect.setSize(sf::Vector2f(50, 50));
	rect.setFillColor(sf::Color(255, 200, 40));
	rect.setPosition(this->position);
}
void Player::Update() {
	this->position.x++;
	rect.setPosition(this->position);
}
void Player::Render() {
	Game::instance->getWindow()->draw(rect);
	std::cout << "rendering player" << std::endl;
}
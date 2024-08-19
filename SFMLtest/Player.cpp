#include "Player.h"
#include "Gameobject.h"
#include <iostream>

namespace agame {

	void Player::Init() {
		this->renderer = std::make_shared<aengine::ShapeRenderer>(aengine::ShapeRenderer(*this, *(aengine::Game::instance->getWindow())));
		auto circle = new sf::CircleShape(30);
		circle->setRadius(30);
		circle->setFillColor(sf::Color(255, 100, 10));
		circle->setPosition(position.getsf());
		position = Vectorf(40, 50);
	}

	void Player::Update() {
		this->position += Vectorf(1, 2);
		renderer->Update();
	}

	void Player::Render() {
		Gameobject::Render();
	}
}
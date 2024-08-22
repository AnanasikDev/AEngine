#include "Player.h"
#include "Gameobject.h"
#include <iostream>

namespace agame {

	Player::Player(std::string name) {
		this->name = name;
	}

	void Player::Init() {
		aengine::ShapeRenderer* r = new aengine::ShapeRenderer(this, (aengine::Game::instance->getWindow()));
		this->renderer.reset(r);
		sf::CircleShape* circle = new sf::CircleShape(30);
		r->shape.reset(circle);
		circle->setRadius(30);
		circle->setFillColor(sf::Color(255, 100, 10));
		position = Vectorf(40, 50);
		circle->setPosition(position.getsf());
		delete r;
		delete circle;
	}

	void Player::Update() {
		//this->position += Vectorf(1, 2);
		renderer->Update();
	}

	void Player::Render() {
		Gameobject::Render();
	}
}
#include "Player.h"
#include "Gameobject.h"
#include "SpriteRenderer.h"
#include "ShapeRenderer.h"
#include "Game.h"
#include <iostream>
#include "Camera.h"
#include "CircleCollider.h"

namespace agame {

	Player::Player(std::string name) : Gameobject(name) {
        this->setRenderer(std::make_unique<aengine::SpriteRenderer>(this, aengine::Game::instance->getWindow(), "resources/Ananasik2.png"));

        auto spriteRenderer = renderer->to<aengine::SpriteRenderer>();

        setPosition(40, 50);
	}

    void Player::start() {
        
    }

	void Player::update() {
        aengine::Vectorf prevPos = getPosition();
        Gameobject::update();
        
        aengine::Vectorf delta;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) delta.x = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) delta.y = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) delta.y = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) delta.x =  1;

        translate(delta * movementSpeed);

        aengine::Camera::translate(getPosition() - prevPos);
	}

	void Player::render() {
		Gameobject::render();
	}
}
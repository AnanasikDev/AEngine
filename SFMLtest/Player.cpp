#include "Player.h"
#include "Gameobject.h"
#include "Renderer.h"
#include "Game.h"
#include <iostream>
#include "Camera.h"
#include "CircleCollider.h"

namespace agame {

	Player::Player(std::string name) : Gameobject(name) {

	}

    void Player::start() {
        this->renderer = std::make_unique<aengine::ShapeRenderer>(this, aengine::Game::instance->getWindow());
        auto shapeRenderer = renderer->to<aengine::ShapeRenderer>();
        shapeRenderer->setShape(std::make_unique<sf::CircleShape>(30));
        auto circle = shapeRenderer->getShapeAs<sf::CircleShape>();

        setCollider(std::make_unique<aengine::CircleCollider>(this, 30));
        setRigidbody(std::make_unique<aengine::Rigidbody>(this));

        circle->setFillColor(sf::Color(255, 100, 10));
        setPosition(40, 50);
        circle->setPosition(getPosition().getsf());

        //aengine::Camera::setPosition(getPosition());
    }

	void Player::update() {
        aengine::Vectorf prevPos = getPosition();
        Gameobject::update();
        
        aengine::Vectorf delta;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) delta.x = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) delta.x =  1;

        if (delta != aengine::Vectorf::zero)
            rigidbody->addForce(delta * movementSpeed);
        translate(delta);

        aengine::Camera::translate(getPosition() - prevPos);
	}

	void Player::render() {
		Gameobject::render();
	}
}
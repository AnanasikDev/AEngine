#include "Core/Engine.h"
#include "Player.h"
#include <memory>

namespace agame {

	Player::Player() : Gameobject() {
        this->setRenderer(std::make_unique<aengine::SpriteRenderer>(this, "assets/Ananasik2.png"));

        auto spriteRenderer = renderer->to<aengine::SpriteRenderer>();

        camera = aengine::context()->getCamera("main");

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

        camera->translate(getPosition() - prevPos);
	}

	void Player::render() {
		Gameobject::render();
	}
}
#include "Core/Engine.h"
#include "Player.h"
#include <memory>

namespace agame {

	Player::Player() : Gameobject() {
        aengine::ShapeRenderer* rend = this->setRenderer(std::make_unique<aengine::ShapeRenderer>(this, std::make_unique<sf::CircleShape>(12)));

        rend->getShapeAs<sf::CircleShape>()->setFillColor(sf::Color(255, 255, 255));

        setCollider(std::make_unique<aengine::CircleCollider>(this));
        setRigidbody(std::make_unique<aengine::Rigidbody>(this));
        rigidbody->makeKinematic();
        rigidbody->onCollisionEvent.Subscribe([this](aengine::Collider* col) { onCollision(col); });

        camera = aengine::context()->getCamera("main");
	}

    void Player::onCollision(aengine::Collider* collider) {
        std::cout << "player collided" << std::endl;
    }

    void Player::start() {
        
    }

	void Player::update() {
        aengine::Vectorf prevPos = getPosition();
        Gameobject::update();
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            rigidbody->addForce(aengine::Vectorf::up * movementSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            rigidbody->addForce(aengine::Vectorf::down * movementSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            rigidbody->addForce(aengine::Vectorf::right * movementSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            rigidbody->addForce(aengine::Vectorf::left * movementSpeed);
        }

        camera->translate(getPosition() - prevPos);
	}

	void Player::render() {
		Gameobject::render();
	}
}
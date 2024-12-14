#include "Core/Engine.h"
#include "Player.h"
#include "GameController.h"
#include <memory>

namespace agame {

	Player::Player() : Gameobject() {
        aengine::ShapeRenderer* rend = this->setRenderer(std::make_unique<aengine::ShapeRenderer>(this, std::make_unique<sf::CircleShape>(radius)));

        rend->getShapeAs<sf::CircleShape>()->setFillColor(sf::Color(255, 255, 255));
        rend->setRelativeOrigin(aengine::Vectorf::half);

        setCollider(std::make_unique<aengine::CircleCollider>(this, radius));
        //setCollider(std::make_unique<aengine::RectCollider>(this, Vectorf()));
        collider->isTrigger = false;
        collider->bounciness = 1;
        collider->onTriggerEvent.Subscribe([this](aengine::Collider* col) { onTrigger(col); });
        collider->onBeforeCollisionEvent.Subscribe([this](aengine::Collider* col) { onBeforeCollision(col); });
        
        setRigidbody(std::make_unique<aengine::Rigidbody>(this));
        rigidbody->makeKinematic();

        isAttachedToCamera = false;
        camera = aengine::context()->getCamera("main");
	}

    void Player::onTrigger(aengine::Collider* trigger) {
        
    }

    void Player::onBeforeCollision(aengine::Collider* collider) {
        if (collider->gameobject->tag == "blob") {
            GameController::addSecondsLeft(1);
            //rigidbody->setAcceleration(aengine::Vectorf::zero);
            //rigidbody->setVelocity(aengine::Vectorf::zero);
            GameController::markBlobHit(collider->gameobject);
        }
        
        if (collider->gameobject->tag == "wall")
        {
            //rigidbody->setAcceleration(aengine::Vectorf::zero);
            GameController::addSecondsLeft(-3);
        }
    }

    void Player::start() {
        
    }

	void Player::update() {
        aengine::Vectorf prevPos = getPosition();
        Gameobject::update();

        aengine::Vectorf force;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            force.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            force.y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            force.x += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            force.x -= 1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && GameController::hookpoints.size() != 0) {

            Gameobject* go = aengine::List::min<aengine::Gameobject*>(GameController::hookpoints, [this](aengine::Gameobject* go)
                { return (go->getPosition() - getPosition()).getLength(); });

            aengine::Vectorf diff = go->getPosition() - getPosition();
            //aengine::Vectorf vec = vec.normalized() * sqrtf(vec.getLength());
            aengine::Vectorf vec = diff.normalized() * 100;
            rigidbody->addForce(vec);
        }

        aengine::Vectorf vel = rigidbody->getVelocity().normalized();
        // -1 - backward
        // 1  - forward
        
        // increase velocity when changing direction - the more you change direction, the more force is applied. For easier movement
        float fac = (-vel.dotProduct(force) + 1) / 2.f + 1;

        force = force * movementSpeed * fac;
        rigidbody->addForce(force);

        camera->translate(getPosition() - prevPos);
        //camera->setPosition(getPosition());
    }

	void Player::render() {
		Gameobject::render();
	}
}
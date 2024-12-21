#include "Core/Engine.h"
#include "Player.h"
#include "GameController.h"
#include "ScoreManager.h"
#include <memory>

namespace agame {

	Player::Player() : Gameobject() {
        
        // init renderer
        aengine::ShapeRenderer* rend = this->setRenderer(std::make_unique<aengine::ShapeRenderer>(this, std::make_unique<sf::CircleShape>(radius)));
        rend->getShapeAs<sf::CircleShape>()->setFillColor(sf::Color(255, 255, 255));
        rend->setRelativeOrigin(aengine::Vectorf::half);

        // init collider
        setCollider(std::make_unique<aengine::CircleCollider>(this, radius));
        collider->isTrigger = false;
        collider->bounciness = 1;
        collider->onTriggerEvent.Subscribe([this](aengine::Collider* col) { onTrigger(col); });
        collider->onBeforeCollisionEvent.Subscribe([this](aengine::Collider* col) { onBeforeCollision(col); });
        
        // init rigidbody
        setRigidbody(std::make_unique<aengine::Rigidbody>(this));
        rigidbody->makeKinematic();

        camera = aengine::Camera::main();
        isAttachedToCamera = false;

        // init trail
        trail = DynamicTrail(16, 5.f);
        trail.setThicknessFunction([this](float v) { return v * radius; });
        trail.setColorFunction([](float v) { return sf::Color(255,255,255 * powf(v, 1), 255 * v); });
        trail.setShiftFunction([this](sf::Vector2f vec) { return camera->worldToScreen(vec).getsf(); });
	}

    void Player::onTrigger(aengine::Collider* trigger) {
        if (trigger->gameobject->tag == "blob") {
            ScoreManager::onBlobCollected();
            rigidbody->addForce((trigger->gameobject->getPosition() - getGameobject()->getPosition()) * blobCollectForce);
            GameController::markBlobHit(trigger->gameobject);
        }
    }

    void Player::onBeforeCollision(aengine::Collider* collider) {
        
        if (collider->gameobject->tag == "wall")
        {
            ScoreManager::onWallHit();
        }
    }

    void Player::start() {
        
    }

	void Player::update() {
        aengine::Vectorf prevPos = getPosition();
        Gameobject::update();

        aengine::Vectorf force;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            force.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            force.y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            force.x += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            force.x -= 1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && GameController::hookpoints.size() != 0) {

            if (!isHooked) {
                hook = aengine::List::min<aengine::Gameobject*>(GameController::hookpoints, [this](aengine::Gameobject* go)
                    { return (go->getPosition() - getPosition()).getLength(); });
            }

            isHooked = true;

            aengine::Vectorf diff = hook->getPosition() - getPosition();
            aengine::Vectorf vec = diff.normalized() * hookForce;
            rigidbody->addForce(vec);
        }
        else {
            isHooked = false;
            hook = nullptr;
        }

        force = force.normalized();
        aengine::Vectorf vel = rigidbody->getVelocity().normalized();
        // -1 - backward
        // 1  - forward
        
        // increase velocity when changing direction - the more you change direction, the more force is applied. For easier movement
        float fac = aengine::rescale(-vel.dotProduct(force), -1, 1, 1, 8);

        force = force * movementSpeed * fac;
        rigidbody->addForce(force);

        camera->translate(getPosition() - prevPos);
        trail.addPoint((getGameobject()->getPosition()).getsf());
        trail.generateVertices();
    }

	void Player::render() {
        trail.render();
		Gameobject::render();
	}
}
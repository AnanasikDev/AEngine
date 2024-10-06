#include "Collectable.h"
#include "Gameobject.h"
#include "Renderer.h"
#include "Game.h"
#include "Collider.h"
#include "Rigidbody.h"
#include <iostream>
#include "Input.h"
#include "Event.h"

namespace agame {

	unsigned int Collectable::collected = 0;

	Collectable::Collectable(std::string name) : Gameobject(name) {
		onLMBDownBackdrop = 0;

		auto shapeRenderer =
			this->setRenderer(std::make_unique<aengine::ShapeRenderer>(this, aengine::Game::instance->getWindow()))
			->to<aengine::ShapeRenderer>();
		shapeRenderer->setShape(std::make_unique<sf::CircleShape>(15));
		shapeRenderer->updateRelativeOrigin();
		shapeRenderer->getShapeAs<sf::CircleShape>()->setFillColor(sf::Color(250, 220, 20));

		setCollider(std::make_unique<aengine::RectCollider>(this, aengine::Vectorf(30, 30)));

		this->setRigidbody(std::make_unique<aengine::Rigidbody>(this));
		rigidbody->setBounciness(0.7f);

		onLMBDownBackdrop = aengine::Input::Mouse::LMB.onPressed.Subscribe([this]() { tryCollect(); });
	}

	void Collectable::start() {
		
	}

	Collectable::~Collectable() {
		Gameobject::~Gameobject();
		aengine::Input::Mouse::LMB.onPressed.Unsubscribe(onLMBDownBackdrop);
	}

	void Collectable::render() {
		Gameobject::render();
	}

	void Collectable::update() {
		Gameobject::update();
	}

	void Collectable::tryCollect() {
		if (this->collider->isPointInside(aengine::Game::instance->worldPos)) {
			collected++;
			this->setPosition(aengine::Vectorf(std::rand() % 500 + 50, 0));
		}
	}
}

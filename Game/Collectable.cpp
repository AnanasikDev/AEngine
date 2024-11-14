#include "Collectable.h"
#include "Core/Engine.h"

namespace agame {

	unsigned int Collectable::collected = 0;

	Collectable::Collectable() : Gameobject() {
		onLMBDownBackdrop = 0;

		auto shapeRenderer =
			this->setRenderer(std::make_unique<aengine::ShapeRenderer>(this, aengine::window()->getWindow()))
			->to<aengine::ShapeRenderer>();
		shapeRenderer->setShape(std::make_unique<sf::CircleShape>(15));
		shapeRenderer->updateRelativeOrigin();
		shapeRenderer->getShapeAs<sf::CircleShape>()->setFillColor(sf::Color(250, 220, 20));

		setCollider(std::make_unique<aengine::CircleCollider>(this, 15));

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
		if (this->collider->isPointInside(aengine::window()->worldPos)) {
			collected++;
			this->setPosition(aengine::Vectorf(std::rand() % 500 + 50, 0));
		}
	}
}

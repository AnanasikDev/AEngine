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
			this->SetRenderer(std::make_unique<aengine::ShapeRenderer>(this, aengine::Game::instance->getWindow()))
			->to<aengine::ShapeRenderer>();
		shapeRenderer->SetShape(std::make_unique<sf::CircleShape>(15));
		shapeRenderer->UpdateRelativeOrigin();
		shapeRenderer->GetShapeAs<sf::CircleShape>()->setFillColor(sf::Color(250, 220, 20));

		SetCollider(std::make_unique<aengine::RectCollider>(this, aengine::Vectorf(30, 30)));

		this->SetRigidbody(std::make_unique<aengine::Rigidbody>(this));
		rigidbody->setBounciness(0.7f);

		onLMBDownBackdrop = aengine::Input::Mouse::LMB.onPressed.Subscribe([this]() { TryCollect(); });
	}

	void Collectable::Start() {
		
	}

	Collectable::~Collectable() {
		Gameobject::~Gameobject();
		aengine::Input::Mouse::LMB.onPressed.Unsubscribe(onLMBDownBackdrop);
	}

	void Collectable::Render() {
		Gameobject::Render();
	}

	void Collectable::Update() {
		Gameobject::Update();
	}

	void Collectable::TryCollect() {
		if (this->collider->IsPointInside(aengine::Game::instance->worldPos)) {
			collected++;
			this->SetPosition(aengine::Vectorf(std::rand() % 500 + 50, 0));
		}
	}
}

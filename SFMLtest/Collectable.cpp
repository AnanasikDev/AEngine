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

		this->renderer = new aengine::ShapeRenderer(this, aengine::Game::instance->getWindow());

		aengine::ShapeRenderer* sp = static_cast<aengine::ShapeRenderer*>(this->renderer);

		sf::CircleShape* circle = new sf::CircleShape();

		sp->shape = circle;

		circle->setFillColor(sf::Color(250, 220, 20));
		circle->setRadius(15);
		sp->SetOrigin(aengine::Vectorf(15, 15));

		//aengine::CircleCollider* collider 
			//= new aengine::CircleCollider(this);
		//collider->radius = 15;

		this->collider = new aengine::RectCollider(this, aengine::Vectorf(30, 30));

		this->rigidbody = new aengine::Rigidbody(this);
		rigidbody->setBounciness(0.7f);

		onLMBDownBackdrop = aengine::Input::Mouse::LMB.onPressed.Subscribe([this]() { TryCollect(); });
	}

	void Collectable::Start() {
		
	}

	Collectable::~Collectable() {
		Gameobject::~Gameobject();
		//aengine::Input::onLeftMouseButtonPressed.Unsubscribe(onLeftMouseButtonPressedCallback);
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

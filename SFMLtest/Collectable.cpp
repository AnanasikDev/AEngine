#include "Collectable.h"
#include "Gameobject.h"
#include "Renderer.h"
#include "Game.h"
#include "Collider.h"
#include <iostream>

namespace agame {
	Collectable::Collectable(std::string name) {
		this->name = name;
	}

	void Collectable::Init() {
		this->renderer = new aengine::ShapeRenderer(this, aengine::Game::instance->getWindow());

		aengine::ShapeRenderer* sp = static_cast<aengine::ShapeRenderer*>(this->renderer);

		sf::CircleShape* circle = new sf::CircleShape();

		sp->shape = circle;

		SetPosition(40, 190);
		circle->setFillColor(sf::Color(250, 220, 20));
		circle->setRadius(15);

		aengine::CircleCollider* collider 
			= new aengine::CircleCollider(this);
		collider->radius = 50;

		this->collider = collider;
		std::cout << "Collectable init" << std::endl;
	}

	void Collectable::Render() {
		Gameobject::Render();
	}

	void Collectable::Update() {
		Gameobject::Update();
		position += aengine::Vectorf(0.5f, 0.3f);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			
			std::cout << (dynamic_cast<aengine::CircleCollider*>(collider)->center - aengine::Game::instance->worldPos).Magnitude() << std::endl;
			
			/*if (this->collider->IsPointInside(aengine::Game::instance->worldPos)) {
				std::cout << "ALSKJFALDKJFASLKDJFA" << std::endl;
			}*/
		}
	}
}

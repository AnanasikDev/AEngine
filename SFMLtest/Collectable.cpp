#include "Collectable.h"
#include "Gameobject.h"
#include "Game.h"

namespace agame {
	Collectable::Collectable(std::string name) {
		this->name = name;
	}

	void Collectable::Init() {
		this->renderer = new aengine::ShapeRenderer(this, aengine::Game::instance->getWindow());

		aengine::ShapeRenderer* sp = static_cast<aengine::ShapeRenderer*>(this->renderer);

		sf::RectangleShape* rect = new sf::RectangleShape();

		sp->shape = rect;

		SetPosition(40, 190);
		rect->setFillColor(sf::Color::Black);
		rect->setSize(Vectorf(40, 90).getsf());
	}

	void Collectable::Render() {
		Gameobject::Render();
	}

	void Collectable::Update() {
		position += Vectorf(1, 3);
		renderer->Update();
	}
}

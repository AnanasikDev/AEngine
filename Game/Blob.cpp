#include "Blob.h"
#include "Core/Engine.h"
#include "GameController.h"

namespace agame {
	Blob::Blob() : Gameobject() {
		float radius = 32;
		aengine::ShapeRenderer* rend = this->setRenderer(std::make_unique<aengine::ShapeRenderer>(this, std::make_unique<sf::CircleShape>(radius)));
		rend->shape->setFillColor(sf::Color(100, 150, 200));
		rend->setRelativeOrigin(aengine::Vectorf::half);

		auto col = setCollider(std::make_unique<aengine::CircleCollider>(this, radius));
		col->isTrigger = true;
		col->bounciness = 1;
		tag = "blob";
	}

	void Blob::update() {
		Gameobject::update();
	}
}

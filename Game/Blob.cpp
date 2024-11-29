#include "Blob.h"
#include "Core/Engine.h"

namespace agame {
	Blob::Blob() : Gameobject() {
		aengine::ShapeRenderer* rend = this->setRenderer(std::make_unique<aengine::ShapeRenderer>(this, std::make_unique<sf::CircleShape>(32)));
		rend->shape->setFillColor(sf::Color(100, 150, 200));
		rend->setRelativeOrigin(aengine::Vectorf::half);

		auto col = setCollider(std::make_unique<aengine::CircleCollider>(this, 32));
		col->bounciness = 1;
	}

	void Blob::update() {
		Gameobject::update();
	}
}

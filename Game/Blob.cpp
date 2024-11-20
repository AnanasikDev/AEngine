#include "Blob.h"
#include "Core/Engine.h"

namespace agame {
	Blob::Blob() : Gameobject() {
		aengine::ShapeRenderer* rend = this->setRenderer(std::make_unique<aengine::ShapeRenderer>(this, std::make_unique<sf::CircleShape>(16)));
		rend->shape->setFillColor(sf::Color(100, 150, 200));
		rend->setRelativeOrigin(aengine::Vectorf::half);

		setCollider(std::make_unique<aengine::CircleCollider>(this, 16));
	}

	void Blob::update() {
		Gameobject::update();
		translate(
			aengine::Vectorf
			(
				(aengine::Random::getFloat() - 0.5f) * 5, 
				(aengine::Random::getFloat() - 0.5f) * 5
			));
	}
}

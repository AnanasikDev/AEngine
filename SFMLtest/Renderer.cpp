#include "Renderer.h"
#include <iostream>
#include "Vector.h"
#include "SFML/Graphics.hpp"
#include "Game.h"

namespace aengine {

	Vectorf Renderer::defaultRelativeOrigin = Vectorf(0.5f, 0.5f);
	const float Renderer::defaultDistance = 64;

	Renderer::Renderer() : gameobject(nullptr), surface(nullptr), distance(defaultDistance) {
		Game::instance->addRenderer(this);
	}

	Renderer::Renderer(Gameobject* gameobject, sf::RenderWindow* surface) : gameobject(gameobject), surface(surface), distance(defaultDistance) {
		Game::instance->addRenderer(this);
	}

	float Renderer::getDistance() const {
		return this->distance;
	}

	void Renderer::setDistance(float distance) {
		this->distance = distance;
		Game::instance->updateRendererDistance(this);
	}

	void Renderer::updateRelativeOrigin() {
		this->setRelativeOrigin(this->origin);
	}

	void Renderer::setRelativeOrigin(const aengine::Vectorf& localOrigin) {
		this->origin = localOrigin;
	}
}
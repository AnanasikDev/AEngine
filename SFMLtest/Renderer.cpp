#include "Renderer.h"
#include <iostream>
#include "Vector.h"
#include "SFML/Graphics.hpp"

namespace aengine {

	Vectorf Renderer::defaultRelativeOrigin = Vectorf(0.5f, 0.5f);

	Renderer::Renderer() {
		gameobject = nullptr;
		surface = nullptr;
	}

	Renderer::Renderer(Gameobject* gameobject, sf::RenderWindow* surface) {
		this->gameobject = gameobject;
		this->surface = surface;
	}

	void Renderer::updateRelativeOrigin() {
		this->setRelativeOrigin(this->origin);
	}

	void Renderer::setRelativeOrigin(const aengine::Vectorf& localOrigin) {
		this->origin = localOrigin;
	}
}
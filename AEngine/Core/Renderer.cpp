#include "Renderer.h"
#include <iostream>
#include "Vector.h"
#include "SFML/Graphics.hpp"
#include "Window.h"
#include "Scene.h"
#include "SceneManager.h"

namespace aengine {

	Vectorf Renderer::defaultRelativeOrigin = Vectorf(0.5f, 0.5f);
	const float Renderer::defaultDistance = 64;

	Renderer::Renderer(Gameobject* gameobject) : gameobject(gameobject), distance(defaultDistance) {
		context()->addRenderer(this);
	}

	float Renderer::getDistance() const {
		return this->distance;
	}

	void Renderer::setDistance(float distance) {
		this->distance = distance;
		context()->updateRendererDistance(this);
	}

	void Renderer::updateRelativeOrigin() {
		this->setRelativeOrigin(this->origin);
	}

	void Renderer::setRelativeOrigin(const aengine::Vectorf& localOrigin) {
		this->origin = localOrigin;
	}
}
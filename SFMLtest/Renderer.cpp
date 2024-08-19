#include "Renderer.h"
#include "Gameobject.h"

namespace aengine {
	void ShapeRenderer::Render() {
		surface->draw(*shape);
	}

	void ShapeRenderer::Update() {
		shape->setPosition(gameobject->position.getsf());
	}

	ShapeRenderer::ShapeRenderer(aengine::Gameobject& gameobject, sf::RenderWindow& surface) {
		this->gameobject = std::make_shared<Gameobject>(gameobject);
		this->surface = std::make_shared<sf::RenderWindow>(surface);
	}
}
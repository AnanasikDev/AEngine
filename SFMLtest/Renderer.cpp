#include "Renderer.h"
#include "Gameobject.h"

namespace aengine {
	void ShapeRenderer::Render() {
		surface->draw(*shape);
	}

	void ShapeRenderer::Update() {
		shape->setPosition(gameobject->position.getsf());
	}

	ShapeRenderer::ShapeRenderer(const ShapeRenderer& other) {
		this->gameobject = other.gameobject;
		this->surface = other.surface;
		this->shape = other.shape;
	}

	ShapeRenderer::ShapeRenderer(const aengine::Gameobject* gameobject, sf::RenderWindow* surface) {
		this->gameobject = std::make_shared<Gameobject>(*gameobject);
		this->surface = surface;
		this->shape = NULL;
	}
}
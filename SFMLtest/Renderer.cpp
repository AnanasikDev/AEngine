#include "Renderer.h"
#include <iostream>
#include "Vector.h"

namespace aengine {
	ShapeRenderer::ShapeRenderer(const ShapeRenderer& other) {
		this->gameobject = other.gameobject;
		this->surface = other.surface;
		this->shape = other.shape;
	}

	ShapeRenderer::ShapeRenderer(aengine::Gameobject* gameobject, sf::RenderWindow* surface) {
		this->gameobject = gameobject;
		this->surface = surface;
		this->shape = nullptr;
	}

	ShapeRenderer::ShapeRenderer(aengine::Gameobject* gameobject, sf::RenderWindow* surface, sf::Shape* shape) {
		this->gameobject = gameobject;
		this->surface = surface;
		this->shape = shape;
	}

	void Renderer::SetOrigin(const aengine::Vectorf& origin) {
		
		auto shapeRenderer = dynamic_cast<ShapeRenderer*>(this);
		if (shapeRenderer != nullptr) {
			
			shapeRenderer->shape->setOrigin(origin.getsf());
			return;
		}

		throw std::exception("Given renderer type is not supported.");
	}

	ShapeRenderer::~ShapeRenderer() {
		delete shape;
	}

	void ShapeRenderer::Render() {
		surface->draw(*shape);
	}

	void ShapeRenderer::Update(const aengine::Vectorf position) {
		shape->setPosition(position.getsf());
	}

	void ShapeRenderer::SetScale(float scale) {
		this->shape->setScale(sf::Vector2f(scale, scale));
	}
}
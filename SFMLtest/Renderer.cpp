#include "Renderer.h"
#include "Gameobject.h"
#include <iostream>

namespace aengine {
	void ShapeRenderer::Render() {
		surface->draw(*shape);
	}

	void ShapeRenderer::Update() {
		shape->setPosition(gameobject->position.getsf());
		
		//shape->move(sf::Vector2f(2, 2));
		//std::cout << "GOpos " << gameobject->position.toStr() << std::endl;
		//std::cout << shape->getPosition().x;
		std::cout << "Shape: " << gameobject << std::endl;
	}

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
}
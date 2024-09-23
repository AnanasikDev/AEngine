#include "Renderer.h"
#include <iostream>
#include "Vector.h"
#include "SFML/Graphics.hpp"

namespace aengine {

	Vectorf Renderer::defaultRelativeOrigin = Vectorf(0.5f, 0.5f);

	ShapeRenderer::ShapeRenderer(const ShapeRenderer& other) {
		this->gameobject = other.gameobject;
		this->surface = other.surface;
		this->shape = other.shape;
		SetRelativeOrigin(defaultRelativeOrigin);
	}

	ShapeRenderer::ShapeRenderer(aengine::Gameobject* gameobject, sf::RenderWindow* surface) {
		this->gameobject = gameobject;
		this->surface = surface;
		this->shape = nullptr;
		SetRelativeOrigin(defaultRelativeOrigin);
	}

	ShapeRenderer::ShapeRenderer(aengine::Gameobject* gameobject, sf::RenderWindow* surface, sf::Shape* shape) {
		this->gameobject = gameobject;
		this->surface = surface;
		this->shape = shape;
		SetRelativeOrigin(defaultRelativeOrigin);
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

	void Renderer::UpdateRelativeOrigin() {
		this->SetRelativeOrigin(this->origin);
	}

	void Renderer::SetRelativeOrigin(const aengine::Vectorf& localOrigin) {
		this->origin = localOrigin;
	}

	void ShapeRenderer::SetRelativeOrigin(const aengine::Vectorf& localOrigin) {
		Renderer::SetRelativeOrigin(localOrigin);
		auto rect = dynamic_cast<sf::RectangleShape*>(shape);
		if (rect != nullptr) {
			rect->setOrigin((Vectorf::fromsf(rect->getSize()) * localOrigin).getsf());
			return;
		}

		auto circle = dynamic_cast<sf::CircleShape*>(shape);
		if (circle != nullptr) {
			circle->setOrigin((localOrigin * circle->getRadius() * 2).getsf());
			return;
		}
	}
}
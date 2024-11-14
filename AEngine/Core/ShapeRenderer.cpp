#include "ShapeRenderer.h"
#include "Window.h"

namespace aengine {

	ShapeRenderer::ShapeRenderer(aengine::Gameobject* gameobject) : Renderer(gameobject) {
		setRelativeOrigin(defaultRelativeOrigin);
	}

	ShapeRenderer::ShapeRenderer(aengine::Gameobject* gameobject, std::unique_ptr<sf::Shape> shape) : Renderer(gameobject) {
		this->shape = std::move(shape);
		setRelativeOrigin(defaultRelativeOrigin);
	}

	ShapeRenderer::~ShapeRenderer() {
		
	}

	void ShapeRenderer::render() {
		window()->getWindow()->draw(*shape);
	}

	void ShapeRenderer::update(const aengine::Vectorf position) {
		shape->setPosition(position.getsf());
	}

	void ShapeRenderer::setScale(float scale) {
		this->shape->setScale(sf::Vector2f(scale, scale));
	}

	void ShapeRenderer::setRelativeOrigin(const aengine::Vectorf& localOrigin) {

		Renderer::setRelativeOrigin(localOrigin);
		auto rect = dynamic_cast<sf::RectangleShape*>(shape.get());
		if (rect != nullptr) {
			rect->setOrigin((Vectorf::fromsf(rect->getSize()) * localOrigin).getsf());
			return;
		}

		auto circle = dynamic_cast<sf::CircleShape*>(shape.get());
		if (circle != nullptr) {
			circle->setOrigin((localOrigin * circle->getRadius() * 2).getsf());
			return;
		}
	}

	sf::Shape* ShapeRenderer::setShape(std::unique_ptr<sf::Shape> _shape)
	{
		this->shape = std::move(_shape);
		return this->shape.get();
	}
}

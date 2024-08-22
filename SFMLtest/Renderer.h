#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"

namespace aengine {

	class Renderer : public Component {
	public:
		std::shared_ptr<class Gameobject> gameobject;
		sf::RenderWindow* surface;

		Renderer() = default;

		virtual void Update() = 0;
		virtual void Render() = 0;
	};

	class ShapeRenderer : public Renderer {
	public:
		std::shared_ptr<sf::Shape> shape;

		ShapeRenderer(const ShapeRenderer& other);
		ShapeRenderer(const aengine::Gameobject* gameobject, sf::RenderWindow* surface);

		void Render() override;
		void Update() override;
	};
}

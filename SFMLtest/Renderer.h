#pragma once

#include <SFML/Graphics.hpp>

namespace aengine {

	class Renderer {
	public:
		class Gameobject* gameobject;
		sf::RenderWindow* surface;

		Renderer() = default;

		virtual void Update() = 0;
		virtual void Render() = 0;
	};

	class ShapeRenderer : public Renderer {
	public:
		sf::Shape* shape;

		ShapeRenderer(const ShapeRenderer& other);
		ShapeRenderer(aengine::Gameobject* gameobject, sf::RenderWindow* surface);

		void Render() override;
		void Update() override;

		~ShapeRenderer();
	};
}

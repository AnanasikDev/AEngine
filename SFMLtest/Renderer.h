#pragma once

#include <SFML/Graphics.hpp>
#include "Vector.h"

namespace aengine {

	class Renderer {
	public:
		class Gameobject* gameobject;
		sf::RenderWindow* surface;

		Renderer() = default;

		virtual void Update(const aengine::Vectorf position) = 0;
		virtual void Render() = 0;

		virtual void SetScale(float scale) = 0;

		void SetOrigin(const aengine::Vectorf& localOrigin);
	};

	class ShapeRenderer : public Renderer {
	public:
		sf::Shape* shape;

		ShapeRenderer(const ShapeRenderer& other);
		ShapeRenderer(aengine::Gameobject* gameobject, sf::RenderWindow* surface);
		ShapeRenderer(aengine::Gameobject* gameobject, sf::RenderWindow* surface, sf::Shape* shape);

		void Render() override;
		void Update(const aengine::Vectorf position) override;
		void SetScale(float scale) override;

		~ShapeRenderer();
	};
}

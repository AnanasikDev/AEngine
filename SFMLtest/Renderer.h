#pragma once

#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Component.h"

namespace aengine {

	class Renderer : public Component {
	public:
		class Gameobject* gameobject;
		sf::RenderWindow* surface;

		/// <summary>
		/// Local relative origin on the renderer within the range 0.0 - 1.0 for each axis
		/// </summary>
		Vectorf origin = defaultRelativeOrigin;

		static Vectorf defaultRelativeOrigin;

		Renderer() = default;

		virtual void update(const aengine::Vectorf position) = 0;
		virtual void render() = 0;

		virtual void setScale(float scale) {};

		/// <summary>
		/// Sets the relative origin point. Automatically applies the changes.
		/// </summary>
		/// <param name="localOrigin">Local relative origin point within range 0.0 - 1.0 for each axis</param>
		virtual void setRelativeOrigin(const aengine::Vectorf& localOrigin);
		void updateRelativeOrigin();
	};

	/// <summary>
	/// Renderer for primitives such as Rectangles and Circles (only they are supported at the moment). Can be used for gameobjects as their renderer.
	/// </summary>
	class ShapeRenderer : public Renderer {
	public:
		std::unique_ptr<sf::Shape> shape;

		//ShapeRenderer(const ShapeRenderer& other);
		ShapeRenderer(aengine::Gameobject* gameobject, sf::RenderWindow* surface);
		ShapeRenderer(aengine::Gameobject* gameobject, sf::RenderWindow* surface, std::unique_ptr<sf::Shape> shape);

		sf::Shape* setShape(std::unique_ptr<sf::Shape> _shape);
		template <typename R>
		R* getShapeAs() {
			return static_cast<R*>(shape.get());
		}

		void render() override;
		void update(const aengine::Vectorf position) override;
		void setScale(float scale) override;

		/// <summary>
		/// Sets the relative origin point. Automatically applies the changes.
		/// </summary>
		/// <param name="localOrigin">Local relative origin point within range 0.0 - 1.0 for each axis</param>
		void setRelativeOrigin(const aengine::Vectorf& localOrigin) override;

		~ShapeRenderer();
	};
}

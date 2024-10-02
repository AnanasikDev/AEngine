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

		virtual void Update(const aengine::Vectorf position) = 0;
		virtual void Render() = 0;

		virtual void SetScale(float scale) {};

		/// <summary>
		/// Sets the relative origin point. Automatically applies the changes.
		/// </summary>
		/// <param name="localOrigin">Local relative origin point within range 0.0 - 1.0 for each axis</param>
		virtual void SetRelativeOrigin(const aengine::Vectorf& localOrigin);
		void UpdateRelativeOrigin();
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

		sf::Shape* SetShape(std::unique_ptr<sf::Shape> _shape);
		template <typename R>
		R* GetShapeAs() {
			return static_cast<R*>(shape.get());
		}

		void Render() override;
		void Update(const aengine::Vectorf position) override;
		void SetScale(float scale) override;

		/// <summary>
		/// Sets the relative origin point. Automatically applies the changes.
		/// </summary>
		/// <param name="localOrigin">Local relative origin point within range 0.0 - 1.0 for each axis</param>
		void SetRelativeOrigin(const aengine::Vectorf& localOrigin) override;

		~ShapeRenderer();
	};
}

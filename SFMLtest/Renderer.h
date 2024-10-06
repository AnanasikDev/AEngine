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
}

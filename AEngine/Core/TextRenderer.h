#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include "Renderer.h"

namespace aengine {

	/// <summary>
	/// Renderer of text on screen, can be used in Gameobjects as their renderer
	/// </summary>
	class TextRenderer : public Renderer {
	public:

		/// <summary>
		/// Loads the default font for later use, should be called once at any point before using text renderers. Can be ommitted if no text is ever used.
		/// </summary>
		static void loadFont();

		/// <summary>
		/// At the moment, only one font type is supported for the whole application.
		/// </summary>
		static sf::Font font;
		static const unsigned int defaultFontSize;
		static const sf::Color defaultColor;

		sf::Text text;

		TextRenderer();
		TextRenderer(class Gameobject* gameobject);
		~TextRenderer() = default;

		void render() override;
		void update(const Vectorf position) override;

		/// <summary>
		/// Sets the relative origin point, considering width of the text. When text is updated the origin point should be updated manually for keeping it correctly aligned (call UpdateRelativeOrigin for that). Automatically applies the changes.
		/// </summary>
		/// <param name="localOrigin">Local relative origin point within range 0.0 - 1.0 for each axis</param>
		void setRelativeOrigin(const aengine::Vectorf& localOrigin) override;
	};
}

#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include "Renderer.h"

namespace aengine {

	/// <summary>
	/// Renders GUI Text on screen. Can be 
	/// </summary>
	class TextRenderer : public Renderer {
	public:

		static void LoadFont();
		static sf::Font font;
		static const unsigned int defaultFontSize;

		sf::Text text;

		TextRenderer();
		~TextRenderer() = default;

		void Render() override;	
		void Update(const Vectorf position) override;
	};
}

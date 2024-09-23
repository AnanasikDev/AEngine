#include "TextRenderer.h"
#include "Game.h"

namespace aengine {

	sf::Font TextRenderer::font;
	const unsigned int TextRenderer::defaultFontSize = 16;

	void TextRenderer::LoadFont() {

		if (!font.loadFromFile("Arial.ttf"))
		{
			throw std::exception("[DEV]: Fail loading Arial.ttf font in Text::Renderer::LoadFont()");
		}
	}

	TextRenderer::TextRenderer() : Renderer() {
		text.setFont(font);
		text.setCharacterSize(defaultFontSize);
		text.setString("Text");
	}

	void TextRenderer::Render() {
		Game::instance->getWindow()->draw(text);
	}

	void TextRenderer::Update(const Vectorf position) {
		text.setPosition(position.getsf());
	}
}

#include "TextRenderer.h"
#include "Game.h"

namespace aengine {

	sf::Font TextRenderer::font;
	const unsigned int TextRenderer::defaultFontSize = 25;
	const sf::Color TextRenderer::defaultColor = sf::Color::Black;

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
		text.setFillColor(defaultColor);
	}

	void TextRenderer::Render() {
		Game::instance->getWindow()->draw(text);
	}

	void TextRenderer::Update(const Vectorf position) {
		text.setPosition(position.getsf());
	}

	void TextRenderer::SetRelativeOrigin(const aengine::Vectorf& localOrigin) {
		Renderer::SetRelativeOrigin(localOrigin);
		text.setOrigin(Vectorf(origin.x * text.getGlobalBounds().width, origin.y * text.getGlobalBounds().height).getsf());
	}
}

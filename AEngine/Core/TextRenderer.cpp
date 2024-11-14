#include "TextRenderer.h"
#include "Window.h"

namespace aengine {

	sf::Font TextRenderer::font;
	const unsigned int TextRenderer::defaultFontSize = 25;
	const sf::Color TextRenderer::defaultColor = sf::Color::Black;

	void TextRenderer::loadFont() {

		if (!font.loadFromFile("resources/Arial.ttf"))
		{
			throw std::exception("[DEV]: Fail loading Arial.ttf font in Text::Renderer::LoadFont()");
		}
	}

	TextRenderer::TextRenderer(Gameobject* gameobject) : Renderer(gameobject) {
		text.setFont(font);
		text.setCharacterSize(defaultFontSize);
		text.setString("Text");
		text.setFillColor(defaultColor);
	}

	TextRenderer::TextRenderer() : Renderer() {
		text.setFont(font);
		text.setCharacterSize(defaultFontSize);
		text.setString("Text");
		text.setFillColor(defaultColor);
	}

	void TextRenderer::render() {
		window()->getWindow()->draw(text);
	}

	void TextRenderer::update(const Vectorf position) {
		text.setPosition(position.getsf());
	}

	void TextRenderer::setRelativeOrigin(const aengine::Vectorf& localOrigin) {
		Renderer::setRelativeOrigin(localOrigin);
		text.setOrigin(Vectorf(origin.x * text.getGlobalBounds().width, origin.y * text.getGlobalBounds().height).getsf());
	}
}

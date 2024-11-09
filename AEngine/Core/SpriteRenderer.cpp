#include "SpriteRenderer.h"

namespace aengine {

	SpriteRenderer::SpriteRenderer(Gameobject* gameobject, sf::RenderWindow* surface, const std::string& textureFileName) : Renderer(gameobject, surface) {

		sprite = std::make_unique<sf::Sprite>();
		loadTexture(textureFileName);

	}

	void SpriteRenderer::update(const Vectorf position) {
		sprite->setPosition(position.getsf());
	}

	void SpriteRenderer::loadTexture(const std::string path) {
		if (!texture.loadFromFile(path)) {
			throw std::exception("[DEV]: Unable to load texture");
		}

		sprite->setTexture(texture);
	}

	void SpriteRenderer::render() {
		surface->draw(*sprite);
	}
}

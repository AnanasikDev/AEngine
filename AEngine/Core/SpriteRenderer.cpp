#include "SpriteRenderer.h"
#include "Window.h"

namespace aengine {

	SpriteRenderer::SpriteRenderer(Gameobject* gameobject, const std::string& textureFileName) : Renderer(gameobject) {

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
		window()->getWindow()->draw(*sprite);
	}
}

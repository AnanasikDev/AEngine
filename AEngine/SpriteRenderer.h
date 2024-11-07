#pragma once

#include "Renderer.h"
#include <memory>

namespace aengine {
	class SpriteRenderer : public Renderer {
	private:
		sf::Texture texture;
	public:
		std::unique_ptr<sf::Sprite> sprite;

		SpriteRenderer(Gameobject* gameobject, sf::RenderWindow* surface, const std::string& textureFileName);

		void loadTexture(const std::string path);

		void update(const Vectorf position) override;
		void render() override;
	};
}

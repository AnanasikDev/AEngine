#pragma once

#include "Renderer.h"
#include <memory>

namespace aengine {
	class SpriteRenderer : public Renderer {
	private:
		sf::Texture texture;
		Vectorf size;

	public:
		std::unique_ptr<sf::Sprite> sprite;

		SpriteRenderer() = delete;
		SpriteRenderer(Gameobject* gameobject, const std::string& textureFileName);

		void loadTexture(const std::string path);
		void setScale(float scale) override;

		/// <summary>
		/// Sets the relative origin point. Automatically applies the changes.
		/// </summary>
		/// <param name="localOrigin">Local relative origin point within range 0.0 - 1.0 for each axis</param>
		void setRelativeOrigin(const Vectorf& localOrigin) override;

		void update(const Vectorf position) override;
		void render() override;
	};
}

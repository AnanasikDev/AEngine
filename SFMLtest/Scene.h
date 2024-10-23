#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>

namespace aengine {

	class Gameobject;
	class Renderer;

	class Scene {
	private:
		/// <summary>
		/// All rendrers present in the world, always ordered by the distance to the camera (from farthest to closest)
		/// </summary>
		std::vector<Renderer*> renderersOrdered;

		/// <summary>
		/// Set individually for each scene so that they can be rendered simultaneously
		/// </summary>
		sf::RenderTarget* renderTarget;
		sf::Color backgroundColor;

	public:
		std::string name;
		std::vector<std::unique_ptr<Gameobject>> gameobjects;

		Scene(sf::RenderTarget* targetTarget);
		~Scene();

		void start();
		void fixedUpdate();
		void update();
		void render();
		void addGameobject(Gameobject* gameobject);
		void addRenderer(Renderer* renderer);
		void updateRendererDistance(Renderer* renderer);

		/// <summary>
		/// Returns true if the given gameobject exists on the scene
		/// </summary>
		const bool contains(Gameobject* gameobject) const;
		void destroyGameobject(Gameobject* gameobject);
	};
}

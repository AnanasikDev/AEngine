#pragma once

#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>

namespace aengine {

	class Gameobject;
	class Renderer;
	class Camera;

	class Scene {
	private:
		/// <summary>
		/// All rendrers present in the world, always ordered by the distance to the camera (from farthest to closest)
		/// </summary>
		std::vector<Renderer*> renderersOrdered;

		/// <summary>
		/// Set individually for each scene so that they can be rendered simultaneously
		/// </summary>
		sf::RenderWindow* renderWindow;
		sf::Color backgroundColor = sf::Color(230, 230, 230);

		std::vector<std::unique_ptr<Camera>> cameras;

	public:
		std::string name;
		std::vector<std::unique_ptr<Gameobject>> gameobjects;

		Scene(const std::string& name, sf::RenderWindow* renderWindow);
		~Scene();

		void start();
		void fixedUpdate();
		void update();
		void render();
		Gameobject* addGameobject(Gameobject* gameobject);
		Gameobject* addGameobject(std::unique_ptr<Gameobject> gameobject);
		void addRenderer(Renderer* renderer);
		const std::vector<Renderer*>& getRenderers() const;
		void updateRendererDistance(Renderer* renderer);

		/// <summary>
		/// Returns true if the given gameobject exists on the scene
		/// </summary>
		const bool contains(Gameobject* gameobject) const;
		void destroyGameobject(Gameobject* gameobject);

		Camera* getCamera(const std::string& name) const;
		void addCamera(Camera* camera);
	};
}

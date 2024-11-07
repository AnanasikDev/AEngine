#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Event.h"
#include "SFML/Graphics/RenderWindow.hpp"

namespace aengine {

	class Scene;

	class SceneManager {
	public:
		static std::vector<std::unique_ptr<Scene>> scenes;

		static Action<Scene*> onSceneChanged;

		static Scene* createScene(const std::string& name, sf::RenderWindow* renderWindow);
		static void deleteAllScenes();
		static Scene* getCurrentScene();
		static void setCurrentScene(const std::string& name);

	private:
		static Scene* m_currentScene;
	};

	Scene* context();
}

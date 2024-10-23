#pragma once

#include <vector>
#include <memory>
#include <string>

namespace aengine {

	class Scene;

	class SceneManager {
	public:
		static SceneManager* instance;

		std::vector<std::unique_ptr<Scene>> scenes;

		SceneManager();
		~SceneManager();
		
		Scene* getCurrentScene() const;
		void setCurrentScene(const std::string& name);

	private:
		Scene* currentScene;
	};
}

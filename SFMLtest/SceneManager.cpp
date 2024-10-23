#include "SceneManager.h"
#include "Scene.h"
#include "List.h"
#include "Debug.h"

namespace aengine {
	SceneManager* instance = nullptr;

	SceneManager::SceneManager() {
		instance = this;
		currentScene = nullptr;
	}

	SceneManager::~SceneManager() {
		/// automatically destroy all objects by destroying unique pointers
		scenes.clear();
	}

	Scene* SceneManager::getCurrentScene() const {
		return currentScene;
	}

	void SceneManager::setCurrentScene(const std::string& name) {
		auto scene = List::findUniquePointerBy<Scene>(scenes, [name](const Scene& scene) { return scene.name == name; });
		if (scene == nullptr) {
			Debug::logException("setCurrentScene could not find a scene of name \"" + name + "\"");
			return;
		}
		this->currentScene = scene;
	}
}

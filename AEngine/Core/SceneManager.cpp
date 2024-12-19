#include "SceneManager.h"
#include "Scene.h"
#include "List.h"
#include "Debug.h"

namespace aengine {
	std::vector<std::unique_ptr<Scene>> SceneManager::scenes;

	Action<Scene*> SceneManager::onSceneChanged;
	Scene* SceneManager::currentScene = nullptr;

	Scene* SceneManager::createScene(const std::string& name, sf::RenderWindow* renderWindow) {
		scenes.push_back(std::make_unique<Scene>(name, renderWindow));
		return scenes[scenes.size() - 1].get();
	}

	void SceneManager::deleteAllScenes() {
		scenes.clear();
	}

	Scene* SceneManager::getCurrentScene() {
		return currentScene;
	}

	void SceneManager::setCurrentScene(const std::string& name) {
		auto scene = List::findUniquePointerBy<Scene>(scenes, [name](Scene* scene) { return scene->name == name; });
		if (scene == nullptr) {
			Debug::logException("setCurrentScene could not find a scene of name \"" + name + "\"");
			return;
		}
		if (currentScene != nullptr && currentScene->name == name)
		{
			Debug::logInfo("new scene name is equal to the current one, no changes made");
			return;
		}

		currentScene = scene;
		onSceneChanged.Invoke(scene);
	}

	Scene* aengine::context() {
		return SceneManager::getCurrentScene();
	}
}

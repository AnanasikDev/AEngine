#include "SceneManager.h"
#include "Scene.h"
#include "List.h"
#include "Debug.h"

namespace aengine {
	std::vector<std::unique_ptr<Scene>> SceneManager::scenes;

	Action<Scene*> SceneManager::onSceneChanged;
	Scene* SceneManager::m_currentScene = nullptr;

	Scene* SceneManager::createScene(const std::string& name) {
		// IMPLEMENT
	}

	void SceneManager::deleteAllScenes() {
		scenes.clear();
	}

	Scene* SceneManager::getCurrentScene() {
		return m_currentScene;
	}

	void SceneManager::setCurrentScene(const std::string& name) {
		auto scene = List::findUniquePointerBy<Scene>(scenes, [name](Scene* scene) { return scene->name == name; });
		if (scene == nullptr) {
			Debug::logException("setCurrentScene could not find a scene of name \"" + name + "\"");
			return;
		}
		if (m_currentScene->name == name)
		{
			Debug::logInfo("new scene name is equal to the current one, no changes made");
			return;
		}

		m_currentScene = scene;
		onSceneChanged.Invoke(scene);
	}

	Scene* aengine::context() {
		return SceneManager::getCurrentScene();
	}
}

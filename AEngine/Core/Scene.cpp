#include "Engine.h"

namespace aengine {

	Scene::Scene(const std::string& name, sf::RenderWindow* targetWindow)
		: name(name), renderWindow(targetWindow) {
	}

	Scene::~Scene() {
		/// automatically destroy all objects by destroying unique pointers
		gameobjects.clear();
	}

	Gameobject* Scene::addGameobject(Gameobject* gameobject) {
		gameobjects.push_back(std::unique_ptr<Gameobject>(gameobject));
		return List::lastUniquePointer(gameobjects);
	}

	Gameobject* Scene::addGameobject(std::unique_ptr<Gameobject> gameobject) {
		gameobjects.push_back(std::move(gameobject));
		return gameobjects.back().get();
	}

	void Scene::addRenderer(Renderer* renderer) {
		for (int i = 0; i < renderersOrdered.size(); i++) {
			if (renderer->getDistance() > renderersOrdered[i]->getDistance()) {
				renderersOrdered.insert(renderersOrdered.begin() + i, renderer);
				return;
			}
		}
		// if renderersOrdered is empty or its distance is minimum
		renderersOrdered.push_back(renderer);
	}

	const std::vector<Renderer*>& Scene::getRenderers() const {
		return renderersOrdered;
	}

	void Scene::updateRendererDistance(Renderer* renderer) {
		List::remove(renderersOrdered, renderer);
		addRenderer(renderer);
	}

	void Scene::setBackgroundColor(sf::Color color) {
		backgroundColor = color;
	}

	sf::Color Scene::getBackgroundColor() const {
		return backgroundColor;
	}

	void Scene::start() {
		for (int i = 0; i < gameobjects.size(); i++) {
			gameobjects[i]->start();
		}
	}

	void Scene::fixedUpdate() {
		for (int i = 0; i < gameobjects.size(); i++) {
			if (!gameobjects[i]->isEnabled || gameobjects[i]->rigidbody == nullptr) continue;

			gameobjects[i]->rigidbody->fixedUpdate();
		}
	}

	void Scene::update() {

		onBeforeUpdate.Invoke();

		Time::update();

		Input::Update();

		for (int i = 0; i < gameobjects.size(); i++) {
			if (!gameobjects[i]->isEnabled) continue;
			
			gameobjects[i]->update();
		}

		/*	TODO: If deltaTime is greater than fixedUpdateInterval
			(On freeze generally when lagging) physics FixedUpdate
			and Update should take that in consideration and
			scale their changes according to deltaTime.
		*/
		if (Time::getFixedDeltaTime() * 1000.f >= Physics::fixedUpdateIntervalMs) {
			fixedUpdate();
			Time::recordFixedUpdate();
		}

		Canvas::update();

		onAfterUpdate.Invoke();
	}

	void Scene::render() {
		Camera::main()->update(); // update screen positions on all gameobjects
		renderWindow->clear(backgroundColor);

		for (int i = 0; i < renderersOrdered.size(); i++) {
			if (renderersOrdered[i]->gameobject != nullptr && !renderersOrdered[i]->gameobject->isEnabled) continue;

			renderersOrdered[i]->gameobject->render();
		}
	}

	const bool Scene::contains(Gameobject* gameobject, bool includeInactive) const {
		for (int i = 0; i < gameobjects.size(); i++) {
			if (gameobjects[i]->isEnabled && gameobjects[i].get() == gameobject)
				return true;
		}
		return false;
	}

	void Scene::destroyGameobject(Gameobject* gameobject)
	{
		List::remove(renderersOrdered, gameobject->renderer.get());
		for (int i = 0; i < gameobjects.size(); i++) {
			if (gameobjects[i].get() == gameobject)
			{
				// removing the unique_ptr hence destroying the object itself
				List::removeAt(gameobjects, i);
			}
		}
	}

	Camera* Scene::getCamera(const std::string& name) const {
		return List::findUniquePointerBy<Camera>(cameras, [name](Camera* cam) { return cam->getName() == name; });
	}

	void Scene::addCamera(Camera* camera) {
		cameras.push_back(std::unique_ptr<Camera>(camera));
	}
}

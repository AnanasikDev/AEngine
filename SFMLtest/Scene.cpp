#include "Game.h"
#include "Gameobject.h"
#include "Rigidbody.h"
#include "Physics.h"
#include <iostream>
#include "Time.h"
#include "Canvas.h"
#include "Input.h"
#include "List.h"
#include "Debug.h"
#include "Renderer.h"
#include "Scene.h"

namespace aengine {

	Scene::Scene(sf::RenderTarget* targetWindow) {
		this->renderTarget = targetWindow;
	}

	Scene::~Scene() {
		/// automatically destroy all objects by destroying unique pointers
		gameobjects.clear();
	}

	void Scene::addGameobject(Gameobject* gameobject) {
		gameobjects.push_back(std::unique_ptr<Gameobject>(gameobject));
	}

	void Scene::addRenderer(Renderer* renderer) {
		for (int i = 0; i < renderersOrdered.size(); i++) {
			if (renderer->getDistance() >= renderersOrdered[i]->getDistance()) {
				renderersOrdered.insert(renderersOrdered.begin() + i, renderer);
				return;
			}
		}
		// if renderersOrdered is empty or its distance is minimum
		renderersOrdered.push_back(renderer);
	}

	void Scene::updateRendererDistance(Renderer* renderer) {
		List::remove(renderersOrdered, renderer);
		addRenderer(renderer);
	}

	void Scene::start() {
		for (int i = 0; i < gameobjects.size(); i++) {
			gameobjects[i]->start();
		}
	}

	void Scene::fixedUpdate() {
		for (int i = 0; i < gameobjects.size(); i++) {
			if (gameobjects[i]->rigidbody != nullptr) {
				gameobjects[i]->rigidbody->fixedUpdate();
			}
		}
	}

	void Scene::update() {

		Time::update();

		Input::Update();

		for (int i = 0; i < gameobjects.size(); i++) {
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
	}

	void Scene::render() {
		renderTarget->clear(backgroundColor);

		for (int i = 0; i < renderersOrdered.size(); i++) {
			renderersOrdered[i]->render();
		}
	}

	const bool Scene::contains(Gameobject* gameobject) const {
		for (int i = 0; i < gameobjects.size(); i++) {
			if (gameobjects[i].get() == gameobject)
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
}
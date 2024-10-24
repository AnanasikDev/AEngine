#include "Game.h"
#include "Engine.h"

namespace aengine {

	Vectorf Camera::position = Vectorf(0,0);
	Scene* Camera::scene = nullptr;

	Camera::Camera() {
		scene = context();
		SceneManager::onSceneChanged.Subscribe([this](Scene* newScene) { this->scene = newScene; }); // no need for unsubscription because it will be deleted at the end
	}

	void Camera::translate(Vectorf delta) {
		position += delta;
		for (int i = 0; i < scene->gameobjects.size(); i++) {
			
			// if attached to camera leave it where it is
			if (scene->gameobjects[i]->isAttachedToCamera) continue;

			scene->gameobjects[i]->translate(-delta, false);
		}
	}

	void Camera::setPosition(Vectorf newPos) {
		translate(newPos - position);
	}
	
	Vectorf Camera::getPosition() {
		return position;
	}
}

#include "Engine.h"

namespace aengine {

	Camera::Camera(const std::string& name) {
		this->name = name;
		cornerPosition = Vectorf();
		scene = context();
		size = window()->getSize();

		SceneManager::onSceneChanged.Subscribe([this](Scene* newScene) { this->scene = newScene; }); // no need for unsubscription because it will be deleted at the end
		scene->addCamera(this);
	}

	void Camera::update() {
		for (int i = 0; i < scene->gameobjects.size(); i++) {

			// if attached to camera leave it where it is
			if (scene->gameobjects[i]->isAttachedToCamera) {
				// set screen position to world position
				scene->gameobjects[i]->screenPosition = 
					scene->gameobjects[i]->getPosition();
			}

			else
			{
				// add position of the camera
				scene->gameobjects[i]->screenPosition = 
					scene->gameobjects[i]->getPosition() - cornerPosition;
			}
		}
	}

	void Camera::translate(Vectorf delta) {
		cornerPosition += delta;
	}

	Vectorf Camera::worldToScreen(Vectorf worldpos) const {
		return worldpos - cornerPosition;
	}

	Vectorf Camera::screenToWorld(Vectorf screenpos) const {
		return cornerPosition + screenpos;
	}

	void Camera::setCornerPosition(Vectorf newPos) {
		translate(newPos - cornerPosition);
	}

	void Camera::setCenterPosition(Vectorf newPos) {
		translate(newPos - size / 2.f - cornerPosition);
	}
	
	Vectorf Camera::getPosition() const {
		return cornerPosition;
	}

	std::string Camera::getName() const {
		return name;
	}

	Camera* Camera::main() {
		return context()->getCamera("main");
	}
}

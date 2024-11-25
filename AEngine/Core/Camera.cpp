#include "Engine.h"

namespace aengine {

	Camera::Camera(const std::string& name) {
		this->name = name;
		position = Vectorf();
		scene = context();
		size = Vectorf::otherFromsf<unsigned int, float>(window()->getWindow()->getSize());

		SceneManager::onSceneChanged.Subscribe([this](Scene* newScene) { this->scene = newScene; }); // no need for unsubscription because it will be deleted at the end
		scene->addCamera(this);
	}

	void Camera::translate(Vectorf delta) {
		position += delta;
		for (int i = 0; i < scene->gameobjects.size(); i++) {
			
			// if attached to camera leave it where it is
			if (scene->gameobjects[i]->isAttachedToCamera) {
				scene->gameobjects[i]->screenPosition = scene->gameobjects[i]->getPosition();
			}

			else
			{
				scene->gameobjects[i]->screenPosition = scene->gameobjects[i]->getPosition() - position;// (position - Vectorf(size.x / 2., size.y / 2.));
			}
		}
	}

	void Camera::setPosition(Vectorf newPos) {
		translate(newPos - position);
	}
	
	Vectorf Camera::getPosition() const {
		return position;
	}

	std::string Camera::getName() const {
		return name;
	}
}

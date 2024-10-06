#include "Camera.h"
#include "Gameobject.h"
#include "Game.h"

namespace aengine {

	Vectorf Camera::position = Vectorf(0,0);

	void Camera::translate(Vectorf delta) {
		position += delta;
		for (int i = 0; i < Game::instance->gameobjects.size(); i++) {
			
			// if attached to camera leave it where it is
			if (Game::instance->gameobjects[i]->isAttachedToCamera) continue;

			Game::instance->gameobjects[i]->translate(-delta, false);
		}
	}

	void Camera::setPosition(Vectorf newPos) {
		translate(newPos - position);
	}
}

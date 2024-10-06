#include "Camera.h"
#include "Gameobject.h"
#include "Game.h"

namespace aengine {

	Vectorf Camera::position = Vectorf(0,0);

	void Camera::Translate(Vectorf delta) {
		position += delta;
		for (int i = 0; i < Game::instance->gameobjects.size(); i++) {
			
			// if attached to camera leave it where it is
			if (Game::instance->gameobjects[i]->isAttachedToCamera) continue;

			Game::instance->gameobjects[i]->Translate(-delta, false);
		}
	}

	void Camera::SetPosition(Vectorf newPos) {
		Translate(newPos - position);
	}
}

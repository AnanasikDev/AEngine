#include "Camera.h"
#include "Gameobject.h"
#include "Game.h"

namespace aengine {

	Vectorf Camera::position = Vectorf(0,0);

	void Camera::Translate(Vectorf delta) {
		position += delta;
		for (Gameobject* go : Game::instance->gameobjects) {
			go->Translate(-delta);
		}
	}

	void Camera::SetPosition(Vectorf newPos) {
		Translate(newPos - position);
	}
}

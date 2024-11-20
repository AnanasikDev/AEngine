#include "Core/Engine.h"
#include "Player.h"
#include "Blob.h"

using namespace aengine;
using namespace agame;

int main() {
	Window window(900, 900, "Game!");
	auto winSize = window.getWindow()->getSize();
	window.getWindow()->setFramerateLimit(60);
	SceneManager::createScene("main", window.getWindow());
	SceneManager::setCurrentScene("main");
	Camera camera("main");

	Gameobject* player = Gameobject::instantiate<Player>("Player");
	player->setPosition(winSize.x / 2.f, winSize.y / 2.f);

	Blob* blob1 = Gameobject::instantiate<Blob>("blob");

	while (window.isRunning()) {

		window.update();
		window.render();
		window.display();
	}

	return 0;
}

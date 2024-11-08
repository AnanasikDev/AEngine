#include <iostream>
#include "../AEngine/enginemain.h"
#include "../AEngine/Engine.h"

using namespace aengine;

int main()
{
    Window window(400, 400, "HEOHE");
	window.getWindow()->setFramerateLimit(60);
	SceneManager::createScene("main", window.getWindow());
	SceneManager::setCurrentScene("main");
	Camera camera("main");

	while (window.isRunning()) {

		window.update();
		window.render();
	}

    return 0;
}
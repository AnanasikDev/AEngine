#include "Core/Engine.h"
#include "Player.h"
#include "Blob.h"
#include "GameController.h"

using namespace aengine;
using namespace agame;

int main() {
	// setup window
	Window window(900, 900, "Game!");
	window.getWindow()->setFramerateLimit(60);
	
	// setup scene
	SceneManager::createScene("main", window.getWindow())->setBackgroundColor(sf::Color(220, 80, 80));
	SceneManager::setCurrentScene("main");
	
	// setup camera
	Camera camera("main");

	// init game systems
	Random::initSeed();
	GameController::init();

	while (window.isRunning()) {

		GameController::preUpdate();
		window.update();
		GameController::postUpdate();

		GameController::preRender();
		window.render();
		GameController::postRender();
		window.display();
	}

	return 0;
}

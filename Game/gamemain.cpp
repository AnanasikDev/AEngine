#include "Core/Engine.h"
#include "GameController.h"

int main() {
	// setup window
	aengine::Window window(900, 900, "Game!");
	window.getWindow()->setFramerateLimit(60);
	
	// setup scene
	aengine::SceneManager::createScene("main", window.getWindow())->setBackgroundColor(sf::Color(220, 80, 80));
	aengine::SceneManager::setCurrentScene("main");
	
	// setup camera
	aengine::Camera camera("main");

	// init game systems
	aengine::Random::initSeed();
	agame::GameController::init();

	while (window.isRunning()) {

		agame::GameController::preUpdate();
		window.update();
		agame::GameController::postUpdate();

		agame::GameController::preRender();
		window.render();
		agame::GameController::postRender();
		window.display();
	}

	return 0;
}

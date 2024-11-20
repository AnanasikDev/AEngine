#include "Core/Engine.h"
#include "Player.h"
#include "Blob.h"
#include "GameController.h"

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
	GameController::player = static_cast<Player*>(player);

	GameController::init();

	Gameobject* scoreDisplay = Gameobject::instantiate("score_display");
	TextRenderer::loadFont();
	TextRenderer* scoreRend = scoreDisplay->setRenderer(std::make_unique<TextRenderer>());
	GameController::textRenderer = scoreRend;
	scoreDisplay->isAttachedToCamera = true;
	scoreRend->setRelativeOrigin(Vectorf::half);
	scoreDisplay->setPosition(winSize.x / 2.f, 25);

	while (window.isRunning()) {

		window.update();
		GameController::update();
		window.render();
		for (auto blob : GameController::blobs) {
			Gizmos::drawSegment(player->getPosition(), blob->getPosition());
		}
		window.display();
	}

	return 0;
}

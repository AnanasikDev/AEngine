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
	SceneManager::createScene("main", window.getWindow())->setBackgroundColor(sf::Color(220, 80, 80));
	SceneManager::setCurrentScene("main");
	Camera camera("main");

	Player* player = Gameobject::instantiate<Player>("Player");
	player->setPosition(winSize.x / 2.f, winSize.y / 2.f);
	GameController::player = player;

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
			Gizmos::drawSegment(player->screenPosition, blob->screenPosition);
		}
		window.display();
	}

	return 0;
}

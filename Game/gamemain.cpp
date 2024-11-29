#include "Core/Engine.h"
#include "Player.h"
#include "Blob.h"
#include "GameController.h"

using namespace aengine;
using namespace agame;

const int BOUNDS_RADIUS = 1300;

int main() {
	Window window(900, 900, "Game!");
	auto winSize = window.getWindow()->getSize();
	window.getWindow()->setFramerateLimit(60);
	SceneManager::createScene("main", window.getWindow())->setBackgroundColor(sf::Color(220, 80, 80));
	SceneManager::setCurrentScene("main");
	Camera camera("main");

	Gameobject* bounds = Gameobject::instantiate("bounds");
	ShapeRenderer* bounds_rend = bounds->setRenderer(std::make_unique<ShapeRenderer>(bounds, std::make_unique<sf::CircleShape>(BOUNDS_RADIUS, 100)));
	auto bounds_circle = bounds_rend->getShapeAs<sf::CircleShape>();
	bounds_circle->setFillColor(sf::Color(230, 230, 230, 255));
	bounds_circle->setOutlineColor(sf::Color(220, 80, 80));
	bounds_circle->setOutlineThickness(10);

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

		float d = player->getPosition().distance(Vectorf::zero);
		if (d > BOUNDS_RADIUS - player->radius) {
			player->rigidbody->setVelocity(Vectorf::zero);
			player->rigidbody->setAcceleration(Vectorf::zero);
			player->rigidbody->addForce(-player->getPosition().normalized() * 300);
		}

		window.render();
		for (auto blob : GameController::blobs) {
			Gizmos::drawSegment(player->screenPosition, blob->screenPosition);
		}
		window.display();
	}

	return 0;
}

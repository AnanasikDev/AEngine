#include "Core/Engine.h"
#include "Player.h"
#include "Blob.h"
#include "GameController.h"

using namespace aengine;
using namespace agame;

const int SCENE_RADIUS = 2000;

int main() {
	Window window(900, 900, "Game!");
	auto winSize = window.getWindow()->getSize();
	window.getWindow()->setFramerateLimit(60);
	SceneManager::createScene("main", window.getWindow());
	SceneManager::setCurrentScene("main");
	Camera camera("main");

	Gameobject* bg = Gameobject::instantiate("background");
	ShapeRenderer* bgrend = bg->setRenderer(std::make_unique<ShapeRenderer>(bg, std::make_unique<sf::CircleShape>(SCENE_RADIUS, 100)));
	auto bgcircle = bgrend->getShapeAs<sf::CircleShape>();
	bgcircle->setFillColor(sf::Color(0,0,0,0));
	bgcircle->setOutlineColor(sf::Color(220, 80, 80));
	bgcircle->setOutlineThickness(10);

	Player* player = Gameobject::instantiate<Player>("Player");
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
		float d = player->getPosition().distance(Vectorf::zero);
		std::cout << player->getPosition() << " " << d << std::endl;
		if (d > SCENE_RADIUS - player->radius) {
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

#include "Core/Engine.h"
#include "Blob.h"
#include "Player.h"
#include "Bomb.h"
#include "GameController.h"

using namespace aengine;

namespace agame {
	float GameController::secondsLeft = 30.f;
	TextRenderer* GameController::textRenderer = nullptr;

	Player* GameController::player = nullptr;

	std::vector<Blob*> GameController::blobs;
	std::vector<Gameobject*> GameController::walls;
	std::vector<Gameobject*> GameController::hookpoints;
	aengine::Gameobject* GameController::bounds;

	std::array<float, 3> GameController::levelThresholds { 0, 12, 19 };
	int GameController::level = 0;

	Action<> GameController::onLevelUpEvent;

	void GameController::init() {
		Vectorf winSize = window()->getSize();

		// ==== Initialize player ==== //

		player = Gameobject::instantiate<Player>("Player");
		player->setPosition(0, 0);
		Camera::main()->setCenterPosition(Vectorf::zero);


		// ==== Initialize score ==== //

		Gameobject* scoreDisplay = Gameobject::instantiate("score_display");
		TextRenderer::loadFont();
		TextRenderer* scoreRend = scoreDisplay->setRenderer(std::make_unique<TextRenderer>(scoreDisplay));
		GameController::textRenderer = scoreRend;
		scoreDisplay->isAttachedToCamera = true;
		scoreRend->setRelativeOrigin(Vectorf::half);
		scoreDisplay->setPosition(winSize.x / 2.f, 25);


		// ==== Initialize bounds ==== //

		bounds = Gameobject::instantiate("bounds");
		ShapeRenderer* bounds_rend = bounds->setRenderer(std::make_unique<ShapeRenderer>(bounds, std::make_unique<sf::CircleShape>(BOUNDS_RADIUS, 100)));
		bounds_rend->setDistance(200);
		auto bounds_circle = bounds_rend->getShapeAs<sf::CircleShape>();
		bounds_circle->setFillColor(sf::Color(230, 230, 230, 255));
		bounds_circle->setOutlineColor(sf::Color(220, 80, 80));
		bounds_circle->setOutlineThickness(10);
		bounds_rend->setRelativeOrigin(Vectorf::half);


		// ==== Initialize levels ==== //

		onLevelUpEvent.Subscribe([]() {

			std::cout << "Level up! current level is " << level << std::endl;

			if (level == 1) beginLevel1();
			else if (level == 2) beginLevel2();
			else if (level == 3) beginLevel3();

			});

		beginLevel0();
	}

	float GameController::getSecondsLeft() {
		return GameController::secondsLeft;
	}

	void GameController::setSecondsLeft(float val) {
		
		secondsLeft = val;
		if (textRenderer != nullptr) textRenderer->text.setString(std::to_string(secondsLeft));
	}

	void GameController::addSecondsLeft(float delta) {
		setSecondsLeft(secondsLeft + delta);
	}

	void GameController::markBlobHit(Gameobject* obj) {
		obj->setPosition(Random::getRandomPointInCircle(BOUNDS_RADIUS - 100));
	}

	float GameController::getDifficultyAt(float t) {
		return powf(t, 0.9f);
	}

	float GameController::getCurrentDifficulty() {
		return getDifficultyAt(Time::getTime());
	}

	int GameController::getCurrentLevel() {
		return level;
	}

	void GameController::beginLevel0() {
		// blobs
		for (int i = 0; i < 13; i++) {
			Time::invoke
			([i]() 
			{
				Blob* blob = Gameobject::instantiate<Blob>("blob" + std::to_string(i));
				blob->setPosition(aengine::Random::getRandomPointInCircle(BOUNDS_RADIUS - 100));
				blobs.push_back(blob);
				blob->tag = "blob";
			}, i / 1.1f + 0.9f);
		}
	}

	void GameController::beginLevel1() {
		// walls
		for (int i = 0; i < 10; i++) {

			Time::invoke
			([i]() 
			{
				Gameobject* wall = Gameobject::instantiate("wall" + std::to_string(i));
				wall->tag = "wall";
				RectCollider* col = wall->setCollider(std::make_unique<RectCollider>(wall, Vectorf(60, 60)));
				SpriteRenderer* rend = wall->setRenderer(std::make_unique<SpriteRenderer>(wall, "assets/wall.png"));
				rend->setRelativeOrigin(Vectorf::half);
				rend->sprite->setScale(Vectorf(3, 3).getsf());

				wall->setPosition(Random::getRandomPointInCircle(BOUNDS_RADIUS - 200));
				rend->setRelativeOrigin(Vectorf::half);
			}, i + 1.);
		}
	}

	void GameController::beginLevel2() {
		// hook points

		for (int i = 0; i < 10; i++) {
			Gameobject* hookpoint = Gameobject::instantiate("hook_" + std::to_string(i));
			hookpoint->setPosition(Random::getRandomPointInCircle(BOUNDS_RADIUS - 100));
			ShapeRenderer* rend = hookpoint->setRenderer(std::make_unique<ShapeRenderer>(hookpoint, std::make_unique<sf::CircleShape>(10)));
			rend->getShapeAs<sf::CircleShape>()->setFillColor(sf::Color::Blue);
			rend->setRelativeOrigin(Vectorf::half);
			hookpoints.push_back(hookpoint);
		}
	}

	void GameController::beginLevel3() {
		// bombs
	}

	void GameController::preUpdate() {

	}

	void GameController::postUpdate() {
		addSecondsLeft(-Time::getDeltaTime());

		float difficulty = getCurrentDifficulty();

		if (level != maxLevel && difficulty > levelThresholds[level + 1]) {
			level++;
			onLevelUpEvent.Invoke();
		}

		float d = player->getPosition().distance(Vectorf::zero);
		if (d > BOUNDS_RADIUS - player->radius) {
			player->setPosition(player->getPosition().normalized() * (BOUNDS_RADIUS - player->radius - 1));
			Vectorf fvelocity = player->rigidbody->getVelocity();
			Vectorf normal = -player->getPosition().normalized(); // radius from 0,0 to player position
			Vectorf impulse1 = fvelocity - normal * fvelocity.dotProduct(normal) * 2;
			player->rigidbody->setVelocity(impulse1 * player->collider->bounciness);
		}
	}

	void GameController::preRender() {

	}

	void GameController::postRender() {
		if (player->isHooked) {
			Gizmos::drawSegment(player->screenPosition, player->hook->screenPosition, sf::Color::White, sf::Color::Black);
		}
	}
}

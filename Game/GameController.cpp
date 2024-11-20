#include "Core/Engine.h"
#include "Blob.h"
#include "Player.h"
#include "Bomb.h"
#include "GameController.h"

using namespace aengine;

namespace agame {
	int GameController::score = 0;
	TextRenderer* GameController::textRenderer = nullptr;

	Player* GameController::player = nullptr;

	std::vector<Blob*> GameController::blobs;
	std::vector<Gameobject*> GameController::walls;
	std::vector<Bomb*> GameController::bombs;

	std::array<float, 3> GameController::levelThresholds { 0, 9, 20 }; // TODO: increase levels intervals
	int GameController::level = 0;

	Action<> GameController::onLevelUpEvent;

	void GameController::init() {
		onLevelUpEvent.Subscribe([]() {

			std::cout << "Level up! current level is " << level << std::endl;

			if (level == 1) beginLevel1();
			else if (level == 2) beginLevel2();

			});

		beginLevel0();
	}

	int GameController::getScore() {
		return score;
	}

	void GameController::setScore(int val) {
		score = val;
		if (textRenderer != nullptr) textRenderer->text.setString(std::to_string(score));
	}

	void GameController::addScore(int delta) {
		setScore(score + delta);
	}

	void GameController::markBlobHit(Gameobject* obj) {
		obj->setPosition(player->getPosition() + Vectorf(
			Random::getFloat(-200, 200),
			Random::getFloat(-200, 200)
		));
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
		for (int i = 0; i < 7; i++) {
			blobs.push_back(Gameobject::instantiate<Blob>("blob" + std::to_string(i)));
		}
	}

	void GameController::beginLevel1() {
		// walls
		for (int i = 0; i < 10; i++) {
			auto pos = player->getPosition() + 
				Vectorf(
					Random::getFloat(-100, 100), 
					Random::getFloat(-100, 100));
			Gameobject* wall = Gameobject::instantiate("wall" + std::to_string(i));
			RectCollider* col = wall->setCollider(std::make_unique<RectCollider>(wall, Vectorf(60, 60)));
			SpriteRenderer* rend = wall->setRenderer(std::make_unique<SpriteRenderer>(wall, "resources/wall.png"));
			rend->setRelativeOrigin(Vectorf::half);
			rend->sprite->setScale(Vectorf(3, 3).getsf());
			
			wall->setPosition(pos);
			rend->setRelativeOrigin(Vectorf::half);
		}
	}

	void GameController::beginLevel2() {
		// bombs
	}


	void GameController::update() {
		float difficulty = getCurrentDifficulty();

		if (level != maxLevel && difficulty > levelThresholds[level + 1]) {
			level++;
			onLevelUpEvent.Invoke();
		}
	}
}

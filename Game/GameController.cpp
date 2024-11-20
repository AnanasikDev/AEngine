#include "Core/Engine.h"
#include "Blob.h"
#include "Player.h"
#include "Bomb.h"
#include "GameController.h"

namespace agame {
	int GameController::score = 0;
	aengine::TextRenderer* GameController::textRenderer = nullptr;

	Player* GameController::player = nullptr;

	std::vector<Blob*> GameController::blobs;
	std::vector<aengine::Gameobject*> GameController::walls;
	std::vector<Bomb*> GameController::bombs;

	std::array<float, 3> GameController::levelThresholds { 0, 9, 20 }; // TODO: increase levels intervals
	int GameController::level = 0;

	aengine::Action<> GameController::onLevelUpEvent;

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

	void GameController::markBlobHit(aengine::Gameobject* obj) {
		obj->setPosition(player->getPosition() + aengine::Vectorf(
			aengine::Random::getFloat(-200, 200),
			aengine::Random::getFloat(-200, 200)
		));
	}

	float GameController::getDifficultyAt(float t) {
		return powf(t, 0.9f);
	}

	float GameController::getCurrentDifficulty() {
		return getDifficultyAt(aengine::Time::getTime());
	}

	int GameController::getCurrentLevel() {
		return level;
	}

	void GameController::beginLevel0() {
		for (int i = 0; i < 7; i++) {
			blobs.push_back(aengine::Gameobject::instantiate<Blob>("blob" + i));
		}
	}

	void GameController::beginLevel1() {
		// walls
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

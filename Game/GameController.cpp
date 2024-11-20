#include "Core/Engine.h"
#include "GameController.h"
#include "Blob.h"
#include "Player.h"

namespace agame {
	int GameController::score = 0;
	aengine::TextRenderer* GameController::textRenderer = nullptr;
	std::vector<Blob*> GameController::blobs;
	Player* GameController::player = nullptr;

	void GameController::init() {
		for (int i = 0; i < 7; i++) {
			blobs.push_back(aengine::Gameobject::instantiate<Blob>("blob" + i));
		}
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

	void GameController::update() {
		// spawn new blobs
		// control difficulty
	}
}

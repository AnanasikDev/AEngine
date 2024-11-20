#include "GameController.h"
#include "Core/Engine.h"

namespace agame {
	int GameController::score = 0;
	aengine::TextRenderer* GameController::textRenderer = nullptr;

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

	void GameController::update() {
		// spawn new blobs
		// control difficulty
	}
}

#include "Core/Engine.h"
#include "GameController.h"
#include "ScoreManager.h"
#include "Player.h"
#include <format>

namespace agame {

	float ScoreManager::secondsLeft = 30.f;
	aengine::TextRenderer* ScoreManager::textRenderer = nullptr;

	void ScoreManager::init() {
		aengine::TextRenderer::loadFont();

		aengine::Gameobject* scoreDisplay = aengine::Gameobject::instantiate("score_display");
		scoreDisplay->setPosition(aengine::window()->getSize().x / 2.f, 25);
		scoreDisplay->isAttachedToCamera = true;

		textRenderer = scoreDisplay->setRenderer(std::make_unique<aengine::TextRenderer>(scoreDisplay));
		textRenderer->setRelativeOrigin(aengine::Vectorf::half);
		textRenderer->setDistance(0);
	}

	float ScoreManager::getSecondsLeft() {
		return ScoreManager::secondsLeft;
	}

	void ScoreManager::setSecondsLeft(float val) {

		secondsLeft = val;
		if (textRenderer != nullptr) textRenderer->text.setString(std::format("{:.3f}", secondsLeft));
	}

	void ScoreManager::addSecondsLeft(float delta) {
		setSecondsLeft(secondsLeft + delta);
	}

	void ScoreManager::onBlobCollected() {
		ScoreManager::addSecondsLeft(0.04f * powf(agame::GameController::player->rigidbody->getVelocity().getLength() * 0.014f, 2.f));
	}

	void ScoreManager::onWallHit() {
		ScoreManager::addSecondsLeft(-6);
	}
}

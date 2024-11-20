#pragma once

#include "Core/TextRenderer.h"
#include "Core/Event.h"
#include <vector>
#include <array>


namespace agame{
	class aengine::Gameobject;

	class GameController {
	private:
		static int score;
		static const int maxLevel = 2;
		static std::array<float, maxLevel+1> levelThresholds;
		static int level;

	public:
		static aengine::TextRenderer* textRenderer;
		static std::vector<class Blob*> blobs;
		static std::vector<aengine::Gameobject*> walls;
		static std::vector<class Bomb*> bombs;
		static class Player* player;
		static aengine::Action<> onLevelUpEvent;

		static void init();

		static int getScore();
		static void setScore(int val);
		static void addScore(int delta);

		static float getDifficultyAt(float t);
		static float getCurrentDifficulty();
		
		static int getCurrentLevel();
		static void beginLevel0();
		static void beginLevel1();
		static void beginLevel2();

		static void markBlobHit(aengine::Gameobject* obj);

		static void update();
	};

}

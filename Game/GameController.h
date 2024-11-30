#pragma once

#include "Core/Event.h"
#include <vector>
#include <array>


namespace agame{
	class aengine::Gameobject;

	class GameController {
	private:
		static float secondsLeft;
		static const int maxLevel = 2;
		static std::array<float, maxLevel+1> levelThresholds;
		static int level;

	public:
		static class aengine::TextRenderer* textRenderer;
		static std::vector<class Blob*> blobs;
		static std::vector<aengine::Gameobject*> walls;
		static std::vector<class Bomb*> hookpoints;
		static class Player* player;
		static aengine::Gameobject* bounds;
		static aengine::Action<> onLevelUpEvent;

		static const int BOUNDS_RADIUS = 1300;

		static void init();

		static float getSecondsLeft();
		static void setSecondsLeft(float val);
		static void addSecondsLeft(float delta);

		static float getDifficultyAt(float t);
		static float getCurrentDifficulty();
		
		static int getCurrentLevel();
		static void beginLevel0();
		static void beginLevel1();
		static void beginLevel2();
		static void beginLevel3();

		static void markBlobHit(aengine::Gameobject* obj);

		static void update();
	};

}

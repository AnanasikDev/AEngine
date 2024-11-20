#pragma once

#include "Core/TextRenderer.h"
#include <vector>

namespace agame{
	
	class GameController {
	private:
		static int score;

	public:
		static aengine::TextRenderer* textRenderer;
		static std::vector<class Blob*> blobs;
		static class Player* player;

		static int getScore();
		static void setScore(int val);
		static void addScore(int delta);

		static void markBlobHit(class aengine::Gameobject* obj);

		static void update();
	};

}

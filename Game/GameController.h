#pragma once

#include "Core/TextRenderer.h"

namespace agame{
	
	class GameController {
	private:
		static int score;

	public:
		static aengine::TextRenderer* textRenderer;

		static int getScore();
		static void setScore(int val);
		static void addScore(int delta);

		static void update();
	};

}

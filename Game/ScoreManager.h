#pragma once

namespace aengine {
	class TextRenderer;
}

namespace agame {
	class ScoreManager {
	private:
		static float secondsLeft;
		static class aengine::TextRenderer* textRenderer;

	public:

		static void init();

		static float getSecondsLeft();
		static void setSecondsLeft(float val);
		static void addSecondsLeft(float delta);

		static void onBlobCollected();
		static void onWallHit();
	};
}

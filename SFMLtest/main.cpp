#include "Game.h"

int main() {

	Game game;
	game.InitWindow();

	while (game.isRunning()) {

		game.Update();

		game.Render();
	}

	return 0;
}

#include "Game.h"
#include "Player.h"
#include "Vector.h"
#include <iostream>

int main() {

	Game game;
	game.InitWindow();
	game.getWindow()->setFramerateLimit(60);

	Player player("Player");
	player.Init();
	game.gameobjects.push_back(&player);

	while (game.isRunning()) {

		game.Update();

		game.Render();
	}

	return 0;
}

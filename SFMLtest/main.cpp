#include "Game.h"
#include "Player.h"
#include "Vector.h"
#include <iostream>

int main() {
	Game game;
	game.InitWindow();
	game.getWindow()->setFramerateLimit(60);

	Player* player = new Player("Player");
	player->Init();
	player->position = Vectorf(40, 50);
	game.gameobjects.push_back(player);

	while (game.isRunning()) {

		game.Update();

		game.Render();
	}

	delete player;

	return 0;
}

#include "Game.h"
#include "Player.h"
#include "Vector.h"
#include "Collectable.h"
#include <iostream>

using namespace aengine;
using namespace agame;

int main() {

	Game game;
	game.InitWindow();
	game.getWindow()->setFramerateLimit(60);

	Player* player = new Player("Player");
	player->Init();
	game.gameobjects.push_back(player);

	Collectable* coin = new Collectable("Coin");
	coin->Init();
	game.gameobjects.push_back(coin);

	while (game.isRunning()) {

		game.Update();

		game.Render();
	}

	delete player;

	return 0;
}

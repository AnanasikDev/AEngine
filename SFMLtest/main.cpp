#include "Game.h"
#include "Player.h"
#include "Vector.h"
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

	while (game.isRunning()) {

		game.Update();
		//std::cout << player->position.toStr();
		//player->Update();
		//player->Render();
		//game.PollEvents();
		//game.getWindow()->display();

		game.Render();
	}

	delete player;

	return 0;
}

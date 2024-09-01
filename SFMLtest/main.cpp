#include "Game.h"
#include "Player.h"
#include "Vector.h"
#include "Collectable.h"
#include <iostream>
#include <vector>

using namespace aengine;
using namespace agame;

int main() {

	Game game;
	game.InitWindow();
	game.getWindow()->setFramerateLimit(60);

	Player* player = new Player("Player");
	player->Init();
	game.gameobjects.push_back(player);

	std::vector<Collectable*> coins;

	for (int i = 0; i < 4; i++) {
		Collectable* coin = new Collectable("Coin");
		coin->Init();
		coin->SetPosition(aengine::Vectorf(std::rand() % 500 + 50, (std::rand() % 100) * -1));
		game.gameobjects.push_back(coin);
	}

	while (game.isRunning()) {

		game.Update();

		game.Render();
	}

	return 0;
}

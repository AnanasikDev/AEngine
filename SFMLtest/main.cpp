#include "Game.h"
#include "Player.h"

int main() {

	Game game;
	game.InitWindow();
	game.getWindow()->setFramerateLimit(60);

	Player* player = new Player("Player");
	player->Init();
	player->position = sf::Vector2f(50, 40);
	game.gameobjects.push_back(player);

	while (game.isRunning()) {

		game.Update();

		game.Render();
	}

	delete player;

	return 0;
}

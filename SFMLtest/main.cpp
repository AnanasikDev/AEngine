#include "Game.h"
#include "Player.h"
#include "Vector.h"
#include <iostream>

int main() {

	Vector<float> a(1, 2);
	Vector<float> b(4, 4.2);

	std::cout << (a + b).toStr();
	return 0;

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

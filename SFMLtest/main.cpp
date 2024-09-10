#include "Game.h"
#include "Player.h"
#include "Vector.h"
#include "Renderer.h"
#include "Collectable.h"
#include <iostream>
#include <vector>
#include "Event.h"

using namespace aengine;
using namespace agame;

int main() {
	Game game;
	game.InitWindow();
	game.getWindow()->setFramerateLimit(60);

	Player* player = new Player("Player");
	player->Init();

	std::vector<Collectable*> coins;

	for (int i = 0; i < 4; i++) {
		Collectable* coin = new Collectable("Coin");
		coin->Init();
		coin->SetPosition(aengine::Vectorf(std::rand() % 500 + 50, (std::rand() % 100) * -1));
	}

	Gameobject* floor = new Gameobject("floor");
	floor->Init();
	auto rect = new sf::RectangleShape(Vectorf(500, 30).getsf());
	rect->setFillColor(sf::Color::Magenta);
	floor->renderer = new aengine::ShapeRenderer(floor, game.getWindow(), rect);
	floor->renderer->SetOrigin(Vectorf(250, 15));
	floor->SetPosition(400, 400);


	while (game.isRunning()) {

		game.Update();

		game.Render();
	}

	return 0;
}

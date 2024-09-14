#include "Game.h"
#include "Player.h"
#include "Vector.h"
#include "Renderer.h"
#include "Collectable.h"
#include "Rigidbody.h"
#include "Collider.h"
#include <iostream>
#include <vector>
#include "Event.h"
#include "Mathf.h"

using namespace aengine;
using namespace agame;

int main() {
	Game game;
	game.InitWindow();
	game.getWindow()->setFramerateLimit(60);

	Player* player = new Player("Player");
	player->Init();

	std::vector<Collectable*> coins;

	auto c1 = new Collectable("Coin1");
	c1->SetPosition(Vectorf(300, 10));
	auto c2 = new Collectable("Coin2");
	c2->SetPosition(Vectorf(300, -30));

	/*for (int i = 0; i < 10; i++) {
		auto c1 = new Collectable("Coin");
		c1->SetPosition(60 + i * 35, i * 10);
	}*/

	Gameobject* floor = new Gameobject("floor");
	floor->Init();
	auto rect = new sf::RectangleShape(Vectorf(800, 30).getsf());
	rect->setFillColor(sf::Color::Magenta);
	floor->renderer = new aengine::ShapeRenderer(floor, game.getWindow(), rect);
	floor->renderer->SetOrigin(Vectorf(400, 15));
	floor->collider = new aengine::RectCollider(floor, Vectorf(800, 30));
	//floor->rigidbody = new Rigidbody(floor);
	floor->SetPosition(400, 600);

	while (game.isRunning()) {

		game.Update();

		game.Render();
	}

	return 0;
}

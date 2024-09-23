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
#include "UIElement.h"
#include "Canvas.h"
#include "TextRenderer.h"

using namespace aengine;
using namespace agame;

int main() {

	Game game;
	game.InitWindow();
	game.getWindow()->setFramerateLimit(60);

	Player* player = new Player("Player");

	std::vector<Collectable*> coins;

	auto c1 = new Collectable("Coin1");
	c1->SetPosition(Vectorf(300, 10));
	auto c2 = new Collectable("Coin2");
	c2->SetPosition(Vectorf(150, -30));
	c2->rigidbody->AddForce(Vectorf(150, 0));

	/*for (int i = 0; i < 10; i++) {
		auto c1 = new Collectable("Coin");
		c1->SetPosition(60 + i * 35, i * 10);
	}*/

	Gameobject* floor = new Gameobject("floor");
	auto rect = new sf::RectangleShape(Vectorf(800, 30).getsf());
	rect->setFillColor(sf::Color::Magenta);
	floor->renderer = new aengine::ShapeRenderer(floor, game.getWindow(), rect);
	floor->renderer->SetRelativeOrigin(Vectorf(0.5f, 0.5f));
	floor->collider = new aengine::RectCollider(floor, Vectorf(800, 30));
	//floor->rigidbody = new Rigidbody(floor);
	floor->SetPosition(400, 600);

	UIElement* button = Canvas::AddUIElement();
	auto shape = new sf::RectangleShape(Vectorf(100, 50).getsf());
	shape->setFillColor(sf::Color::Cyan);
	button->getGameobject()->renderer = new ShapeRenderer(button->getGameobject(), game.getWindow(), shape);
	button->bounds = Bounds(Vectorf(0, 0), Vectorf(100, 50));
	button->onLMBPressed.Subscribe([]() { std::cout << "BUTTON IS DOWN" << std::endl; });
	button->onLMBReleased.Subscribe([]() { std::cout << "BUTTON IS UP" << std::endl; });
	button->getGameobject()->renderer->SetRelativeOrigin(Vectorf(0, 0));

	TextRenderer::LoadFont();

	Gameobject* txt = new Gameobject("MyText");
	txt->SetPosition(game.getWindow()->getSize().x / 2.f, 20);
	TextRenderer* textRenderer = new TextRenderer();
	textRenderer->SetRelativeOrigin(Vectorf::zero);
	txt->renderer = textRenderer;

	game.Start();

	while (game.isRunning()) {

		game.Update();
		textRenderer->text.setString(std::to_string(Collectable::collected));
		textRenderer->UpdateRelativeOrigin();

		game.Render();
	}

	return 0;
}

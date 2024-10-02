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
#include "Time.h"

using namespace aengine;
using namespace agame;

int main() {
	Game game;
	game.InitWindow();
	game.getWindow()->setFramerateLimit(60);

	//Player* player = new Player("Player");

	auto gg = new Gameobject();
	
	//std::vector<Collectable*> coins;

	/*auto c1 = new Collectable("Coin1");
	c1->SetPosition(Vectorf(300, 400));
	c1->rigidbody->AddForce(Vectorf(-80, -130));
	auto c2 = new Collectable("Coin2");
	c2->SetPosition(Vectorf(50, 500));
	c2->rigidbody->AddForce(Vectorf(80, -200));*/

	Gameobject* block1 = new Gameobject("block1");
	sf::RectangleShape* block1rect = new sf::RectangleShape();
	block1rect->setSize(Vectorf(90, 90).getsf());
	block1rect->setFillColor(sf::Color::Green);
	std::unique_ptr<ShapeRenderer> block1rend = std::make_unique<ShapeRenderer>(block1, game.getWindow(), block1rect);
	block1rend->SetRelativeOrigin(Vectorf::half);
	block1->SetRenderer(std::move(block1rend));
	block1->collider = std::make_unique<RectCollider>(block1, Vectorf(90, 90));
	block1->rigidbody = new Rigidbody(block1);
	block1->SetPosition(100, 100);
	block1->rigidbody->makeKinematic();
	block1->rigidbody->AddForce(Vectorf(200, 0));


	Gameobject* block2 = new Gameobject("block2");
	sf::RectangleShape* block2rect = new sf::RectangleShape();
	block2rect->setSize(Vectorf(90, 90).getsf());
	block2rect->setFillColor(sf::Color(0, 200, 0));
	std::unique_ptr<ShapeRenderer> block2rend = std::make_unique<ShapeRenderer>(block2, game.getWindow(), block2rect);
	block2rend->SetRelativeOrigin(Vectorf::half);
	block2->SetRenderer<ShapeRenderer>(std::move(block2rend));
	block2->collider = std::make_unique<RectCollider>(block2, Vectorf(90, 90));

	block2->rigidbody = new Rigidbody(block2);
	block2->SetPosition(600, 100);
	block2->rigidbody->makeKinematic();
	block2->rigidbody->setMass(10.f);
	block2->rigidbody->AddForce(Vectorf(-80, 0));

	Gameobject* block3 = new Gameobject("block3");
	sf::RectangleShape* block3rect = new sf::RectangleShape();
	block3rect->setSize(Vectorf(40, 40).getsf());
	block3rect->setFillColor(sf::Color(0, 0, 0));
	std::unique_ptr<ShapeRenderer> block3rend = std::make_unique<ShapeRenderer>(block3, game.getWindow(), block3rect);
	block3rend->SetRelativeOrigin(Vectorf::half);
	block3->SetRenderer(std::move(block3rend));
	block3->SetPosition(400, 400);

	/*for (int i = 0; i < 10; i++) {
		auto c1 = new Collectable("Coin");
		c1->SetPosition(60 + i * 35, i * 10);
	}*/

	/*Gameobject* floor = new Gameobject("floor");
	auto rect = new sf::RectangleShape(Vectorf(800, 30).getsf());
	rect->setFillColor(sf::Color::Magenta);
	floor->renderer = new aengine::ShapeRenderer(floor, game.getWindow(), rect);
	floor->renderer->SetRelativeOrigin(Vectorf::half);
	floor->collider = new aengine::RectCollider(floor, Vectorf(800, 30));
	floor->rigidbody = new Rigidbody(floor);
	floor->rigidbody->makeStatic();
	floor->SetPosition(400, 550);*/

	/*UIElement* button = Canvas::AddUIElement();
	auto shape = new sf::RectangleShape(Vectorf(100, 50).getsf());
	shape->setFillColor(sf::Color::Cyan);
	button->getGameobject()->renderer = new ShapeRenderer(button->getGameobject(), game.getWindow(), shape);
	button->bounds = Bounds(Vectorf(0, 0), Vectorf(100, 50));
	button->onLMBPressed.Subscribe([]() { std::cout << "BUTTON IS DOWN" << std::endl; });
	button->onLMBReleased.Subscribe([]() { std::cout << "BUTTON IS UP" << std::endl; });
	button->getGameobject()->renderer->SetRelativeOrigin(Vectorf::zero);

	TextRenderer::LoadFont();

	Gameobject* txt = new Gameobject("MyText");
	txt->SetPosition(game.getWindow()->getSize().x / 2.f, 20);
	TextRenderer* textRenderer = new TextRenderer();
	textRenderer->SetRelativeOrigin(Vectorf::zero);
	txt->renderer = textRenderer;
	txt->isAttachedToCamera = true;*/

	Time::InvokeRepeating([]() { std::cout << "Hello!" << std::endl; }, 0, 1.f);

	game.Start();

	while (game.isRunning()) {

		game.Update();
		//textRenderer->text.setString(std::to_string(Collectable::collected));
		//textRenderer->UpdateRelativeOrigin();

		//std::cout << Time::getTime() / 1000.f << "  " << Mathf::Repeat(Time::getTime() / 1000.f, 0, 200) << std::endl;

		//block3->SetPosition(Vectorf(Mathf::Repeat(Time::getTime(), 0, 200), block3->getPosition().y));

		game.Render();
	}

	return 0;
}

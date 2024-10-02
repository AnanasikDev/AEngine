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

	Player* player = new Player("Player");

	auto c1 = new Collectable("Coin1");
	c1->SetPosition(Vectorf(300, 400));
	c1->rigidbody->AddForce(Vectorf(-80, -130));
	auto c2 = new Collectable("Coin2");
	c2->SetPosition(Vectorf(50, 500));
	c2->rigidbody->AddForce(Vectorf(80, -200));

	Gameobject* block1 = new Gameobject("block1");
	auto block1rend = block1->SetRenderer(std::make_unique<ShapeRenderer>(block1, game.getWindow()));
	block1rend->SetShape(std::make_unique<sf::RectangleShape>());
	auto block1rect = block1rend->GetShapeAs<sf::RectangleShape>();
	block1rect->setSize(Vectorf(90, 90).getsf());
	block1rect->setFillColor(sf::Color::Green);
	block1rend->SetRelativeOrigin(Vectorf::half);
	block1->collider = std::make_unique<RectCollider>(block1, Vectorf(90, 90));
	block1->SetRigidbody(std::make_unique<Rigidbody>(block1));
	block1->SetPosition(100, 100);
	block1->rigidbody->makeKinematic();
	block1->rigidbody->AddForce(Vectorf(200, 0));

	Gameobject* block2 = new Gameobject("block2");
	auto block2rend = block2->SetRenderer(std::make_unique<ShapeRenderer>(block2, game.getWindow()));
	block2rend->SetShape(std::make_unique<sf::RectangleShape>());
	auto block2rect = block2rend->GetShapeAs<sf::RectangleShape>();
	block2rect->setSize(Vectorf(90, 90).getsf());
	block2rect->setFillColor(sf::Color(0, 200, 0));
	block2rend->SetRelativeOrigin(Vectorf::half);
	block2->collider = std::make_unique<RectCollider>(block2, Vectorf(90, 90));
	block2->SetRigidbody(std::make_unique<Rigidbody>(block2));
	block2->SetPosition(600, 100);
	block2->rigidbody->makeKinematic();
	block2->rigidbody->setMass(10.f);
	block2->rigidbody->AddForce(Vectorf(-80, 0));

	Gameobject* floor = new Gameobject("floor");

 	auto floorRend = floor->SetRenderer(std::make_unique<ShapeRenderer>(floor, game.getWindow()))->to<ShapeRenderer>();

	floorRend->SetShape(std::make_unique<sf::RectangleShape>(Vectorf(800, 30).getsf()));
	
	auto floorRect = floorRend->GetShapeAs<sf::RectangleShape>();
	floorRect->setFillColor(sf::Color::Magenta);
	floor->renderer->SetRelativeOrigin(Vectorf::half);
	
	floor->SetCollider(std::make_unique<RectCollider>(floor, Vectorf(800, 30)));
	floor->SetRigidbody(std::make_unique<Rigidbody>(floor));
	floor->rigidbody->makeStatic();
	floor->SetPosition(400, 550);

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

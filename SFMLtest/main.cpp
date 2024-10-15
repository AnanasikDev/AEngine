#include "Engine.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include "Debug.h"

using namespace aengine;
using namespace agame;

int main() {
	Game game;
	game.initWindow();
	game.getWindow()->setFramerateLimit(60);

	Player* player = new Player("Player");

	auto c1 = new Collectable("Coin1");
	c1->setPosition(Vectorf(300, 400));
	c1->rigidbody->addForce(Vectorf(-80, -130));
	auto c2 = new Collectable("Coin2");
	c2->setPosition(Vectorf(50, 500));
	c2->rigidbody->addForce(Vectorf(80, -200));

	Gameobject* block1 = new Gameobject("block1");
	auto block1rend = block1->setRenderer(std::make_unique<ShapeRenderer>(block1, game.getWindow()));
	block1rend->setShape(std::make_unique<sf::RectangleShape>());
	auto block1rect = block1rend->getShapeAs<sf::RectangleShape>();
	block1rect->setSize(Vectorf(90, 90).getsf());
	block1rect->setFillColor(sf::Color::Green);
	block1rend->setRelativeOrigin(Vectorf::half);
	block1->collider = std::make_unique<RectCollider>(block1, Vectorf(90, 90));
	block1->setRigidbody(std::make_unique<Rigidbody>(block1));
	block1->setPosition(100, 100);
	block1->rigidbody->makeKinematic();
	block1->rigidbody->addForce(Vectorf(200, 0));

	Gameobject* block2 = new Gameobject("block2");
	auto block2rend = block2->setRenderer(std::make_unique<ShapeRenderer>(block2, game.getWindow()));
	block2rend->setShape(std::make_unique<sf::RectangleShape>());
	auto block2rect = block2rend->getShapeAs<sf::RectangleShape>();
	block2rect->setSize(Vectorf(90, 90).getsf());
	block2rect->setFillColor(sf::Color(0, 200, 0));
	block2rend->setRelativeOrigin(Vectorf::half);
	block2->collider = std::make_unique<RectCollider>(block2, Vectorf(90, 90));
	block2->setRigidbody(std::make_unique<Rigidbody>(block2));
	block2->setPosition(600, 100);
	block2->rigidbody->makeKinematic();
	block2->rigidbody->setMass(10.f);
	block2->rigidbody->addForce(Vectorf(-80, 0));

	Gameobject* floor = new Gameobject("floor");

 	auto floorRend = floor->setRenderer(std::make_unique<ShapeRenderer>(floor, game.getWindow()))->to<ShapeRenderer>();

	floorRend->setShape(std::make_unique<sf::RectangleShape>(Vectorf(800, 30).getsf()));
	
	auto floorRect = floorRend->getShapeAs<sf::RectangleShape>();
	floorRect->setFillColor(sf::Color::Magenta);
	floor->renderer->setRelativeOrigin(Vectorf::half);
	
	floor->setCollider(std::make_unique<RectCollider>(floor, Vectorf(800, 30)));
	floor->setRigidbody(std::make_unique<Rigidbody>(floor));
	floor->rigidbody->makeStatic();
	floor->setPosition(400, 550);

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


	Line a(Vectorf(0, 0) * 10, Vectorf(6, 4) * 10);
	Line b(Vectorf(0, 4) * 10, Vectorf(6, 0) * 10);
	Line c(Vectorf(0, 2) * 10, Vectorf(10, 2) * 10);
	Line d(Vectorf(2, -1) * 10, Vectorf(2, 5) * 10);
	Line e(Vectorf(6, -1) * 10, Vectorf(6, 5) * 10);
	Line f(Vectorf(6, 100) * 10, Vectorf(6, 3) * 10);
	Line g(Vectorf(-2, 15) * 10, Vectorf(25, 15) * 10);

	//Line l1(Vectorf(-5, -4) * 10, Vectorf(1, 8) * 10);
	//Line l2(Vectorf(5, 6) * 10, Vectorf(-9, -1) * 10);

	Line l1(Vectorf(0, 0), Vectorf(10, 10) * 10);
	Bounds bounds(Vectorf(-10, -10) * 10, Vectorf(15, 25) * 10);

	Time::invokeRepeating([]() { std::cout << "Hello!" << std::endl; }, 0, 1.f);

	game.start();
	auto window = game.getWindow();
	Vectorf windowSize = Vectorf(window->getSize().x, window->getSize().y);

	Line axisX(Vectorf(0, windowSize.y / 2.f), Vectorf(windowSize.x, windowSize.y / 2.f));
	Line axisY(Vectorf(windowSize.x / 2.f, 0), Vectorf(windowSize.x / 2.f, windowSize.y));

	Line intersection;

	while (game.isRunning()) {

		game.update();

		Debug::logInfo("hi");

		Debug::logWarning("MyWarning!");
		Debug::logError("MyError!");
		//textRenderer->text.setString(std::to_string(Collectable::collected));
		//textRenderer->UpdateRelativeOrigin();

		//std::cout << Time::getTime() / 1000.f << "  " << Mathf::Repeat(Time::getTime() / 1000.f, 0, 200) << std::endl;

		//block3->SetPosition(Vectorf(Mathf::Repeat(Time::getTime(), 0, 200), block3->getPosition().y));

		game.render();

		axisX.render(window, Vectorf::zero, 1, sf::Color::Red);
		axisY.render(window, Vectorf::zero, 1, sf::Color::Green);

		Vectorf shift = -aengine::Camera::getPosition(); // windowSize / 2.f;
		Vectorf mouse = aengine::Input::getMousePosition() - shift;

		l1.render(window, shift, 1, sf::Color::Blue);
		bounds.render(window, shift, 1, sf::Color::Yellow);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			l1.setPoint1(mouse);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			l1.setPoint2(mouse);
		}

		auto i = Line::getSegmentBoundsIntersection(l1, bounds);
		if (i.has_value())
		{
			intersection.setPoint1(i.value().p1);
			intersection.setPoint2(i.value().p2);
		}
		//else
		//	std::cout << "No point" << std::endl;
		std::cout << std::boolalpha << Line::areSegmentBoundsIntesecting(l1, bounds) << std::endl;
		
		intersection.render(window, shift, 1, sf::Color::Magenta);

		/*a.render(window, shift, 1);
		b.render(window, shift, 1);
		c.render(window, shift, 1);
		d.render(window, shift, 1);
		e.render(window, shift, 1);
		f.render(window, shift, 1);
		g.render(window, shift, 1);*/

		game.display();
	}

	return 0;
}

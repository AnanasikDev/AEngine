#include "Core/Engine.h"
#include "Player.h"
#include "Collectable.h"

using namespace aengine;
using namespace agame;

int main() {
	Window window(1200, 900, "Tech demo of AEngine");
	window.getWindow()->setFramerateLimit(60);
	SceneManager::createScene("main", window.getWindow());
	SceneManager::setCurrentScene("main");
	Camera camera("main");

	Gameobject* player = Gameobject::instantiate<Player>("Player");

	Collectable* coin1 = Gameobject::instantiate<Collectable>("coin1");
	coin1->setPosition(Vectorf(400, 0));
	Collectable* coin2 = Gameobject::instantiate<Collectable>("coin2");
	coin2->setPosition(Vectorf(700, 0));

	Gameobject* block1 = Gameobject::instantiate("block1");
	auto block1rend = block1->setRenderer(std::make_unique<ShapeRenderer>(block1));
	block1rend->setShape(std::make_unique<sf::RectangleShape>());
	auto block1rect = block1rend->getShapeAs<sf::RectangleShape>();
	block1rect->setSize(Vectorf(90, 90).getsf());
	block1rect->setFillColor(sf::Color::Green);
	block1rend->setRelativeOrigin(Vectorf::half);
	block1->setCollider(std::make_unique<RectCollider>(block1, Vectorf(90, 90)));
	block1->setRigidbody(std::make_unique<Rigidbody>(block1));
	block1->setPosition(100, 100);
	block1->rigidbody->makeKinematic();
	block1->rigidbody->addForce(Vectorf(200, 0));

	Gameobject* block2 = Gameobject::instantiate("block2");
	auto block2rend = block2->setRenderer(std::make_unique<ShapeRenderer>(block2));
	block2rend->setShape(std::make_unique<sf::RectangleShape>());
	auto block2rect = block2rend->getShapeAs<sf::RectangleShape>();
	block2rect->setSize(Vectorf(90, 90).getsf());
	block2rect->setFillColor(sf::Color(0, 200, 0));
	block2rend->setRelativeOrigin(Vectorf::half);
	block2->setCollider(std::make_unique<RectCollider>(block2, Vectorf(90, 90)));
	block2->setRigidbody(std::make_unique<Rigidbody>(block2));
	block2->setPosition(600, 100);
	block2->rigidbody->makeKinematic();
	block2->rigidbody->setMass(10.f);
	block2->rigidbody->addForce(Vectorf(-80, 0));

	for (int i = 0; i < 1; i++) {
		Gameobject* block = Gameobject::instantiate("block");
		auto blockrend = block->setRenderer(std::make_unique<ShapeRenderer>(block));
		blockrend->setShape(std::make_unique<sf::RectangleShape>());
		auto blockrect = blockrend->getShapeAs<sf::RectangleShape>();
		blockrect->setSize(Vectorf(30, 30).getsf());
		blockrect->setFillColor(sf::Color(150, 0, 170));
		blockrend->setRelativeOrigin(Vectorf::half);
		block->setCollider(std::make_unique<RectCollider>(block, Vectorf(30, 30)));
		block->setRigidbody(std::make_unique<Rigidbody>(block));
		block->setPosition(400, 0 + i * 40);
		block->rigidbody->makeDynamic();
		block->rigidbody->setMass(3.f);
	}

	Gameobject* floor = Gameobject::instantiate("floor");

	auto floorRend = floor->setRenderer(std::make_unique<ShapeRenderer>(floor))->to<ShapeRenderer>();

	floorRend->setShape(std::make_unique<sf::RectangleShape>(Vectorf(800, 30).getsf()));

	auto floorRect = floorRend->getShapeAs<sf::RectangleShape>();
	floorRect->setFillColor(sf::Color::Magenta);
	floor->renderer->setRelativeOrigin(Vectorf::half);

	floor->setCollider(std::make_unique<RectCollider>(floor, Vectorf(800, 30)));
	floor->setRigidbody(std::make_unique<Rigidbody>(floor));
	floor->rigidbody->makeStatic();
	floor->setPosition(400, 550);
	
	TextRenderer::loadFont();
	
	Gameobject* txt = Gameobject::instantiate("MyText");
	txt->setPosition(window.getWindow()->getSize().x / 2.f, 20);
	auto textRenderer = txt->setRenderer(std::make_unique<aengine::TextRenderer>(txt));
	std::cout << textRenderer->text.getCharacterSize() << std::endl;
	txt->isAttachedToCamera = true;

	Gameobject* point = Gameobject::instantiate("point");
	point->setRenderer(std::make_unique<ShapeRenderer>(point, std::make_unique<sf::CircleShape>(40)));
	point->setPosition(Vectorf(100, 100));
	point->isAttachedToCamera = false;

	Line l1(Vectorf(0, 0), Vectorf(10, 10) * 10);
	Bounds bounds(Vectorf(-10, -10) * 10, Vectorf(15, 25) * 10);

	Vectorf windowSize = Vectorf(window.getWindow()->getSize().x, window.getWindow()->getSize().y);

	float circle_radius = 60;
	Vectorf circle_pos = Vectorf(90, 90);

	Line axisX(Vectorf(0, windowSize.y / 2.f), Vectorf(windowSize.x, windowSize.y / 2.f));
	Line axisY(Vectorf(windowSize.x / 2.f, 0), Vectorf(windowSize.x / 2.f, windowSize.y));

	Line intersection;
	Line intersection2;

	const std::vector<Renderer*> r = context()->getRenderers();
	for (int i = 0; i < r.size(); i++) {
		std::cout << r[i]->gameobject->name << std::endl;
	}

	while (window.isRunning()) {

		window.update();
		point->setPosition(Mathf::lerp(0, 100, Mathf::pingpong(Time::getTime(), 1.)), point->getPosition().y);

		window.render();

		axisX.render(window.getWindow(), Vectorf::zero, 1, sf::Color::Red);
		axisY.render(window.getWindow(), Vectorf::zero, 1, sf::Color::Green);

		Vectorf shift = -camera.getPosition();
		Vectorf mouse = aengine::Input::getMousePosition() - shift;
		l1.render(window.getWindow(), shift, 1, sf::Color::Blue);
		bounds.render(window.getWindow(), shift, 1, sf::Color::Yellow);

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
		intersection.render(window.getWindow(), shift, 1, sf::Color::Magenta);

		i = Line::getSegmentCircleIntersection(l1, circle_pos, circle_radius);
		if (i.has_value())
		{
			intersection2.setPoint1(i.value().p1);
			intersection2.setPoint2(i.value().p2);
		}
		Gizmos::drawCircle(circle_pos + shift, circle_radius);
		intersection2.render(window.getWindow(), shift, 1, sf::Color::Cyan);

		window.display();
	}

	return 0;
}

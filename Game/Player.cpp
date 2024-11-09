#include "Core/Engine.h"
#include "Player.h"
#include <memory>

namespace agame {

	Player::Player(std::string name) : Gameobject(name) {
        //this->setRenderer(std::make_unique<aengine::SpriteRenderer>(this, aengine::window()->getWindow(), "resources/Ananasik2.png"));

        //auto spriteRenderer = renderer->to<aengine::SpriteRenderer>();

        auto rend = this->setRenderer(std::make_unique<aengine::ShapeRenderer>(this, aengine::window()->getWindow()));
        rend->setShape(std::make_unique<sf::RectangleShape>());
        auto rect = rend->getShapeAs<sf::RectangleShape>();
        rect->setSize(aengine::Vectorf(90, 90).getsf());
        rect->setFillColor(sf::Color::Red);
        rend->setRelativeOrigin(aengine::Vectorf::half);

        camera = aengine::context()->getCamera("main");

        setPosition(40, 50);
	}

    void Player::start() {
        
    }

	void Player::update() {
        aengine::Vectorf prevPos = getPosition();
        Gameobject::update();
        
        aengine::Vectorf delta;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) delta.x = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) delta.y = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) delta.y = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) delta.x =  1;

        translate(delta * movementSpeed);

        camera->translate(getPosition() - prevPos);
	}

	void Player::render() {
		Gameobject::render();
	}
}
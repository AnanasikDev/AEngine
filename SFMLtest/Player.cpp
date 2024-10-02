#include "Player.h"
#include "Gameobject.h"
#include "Renderer.h"
#include "Game.h"
#include <iostream>
#include "Camera.h"

namespace agame {

	Player::Player(std::string name) : Gameobject(name) {

        Gameobject* child = new Gameobject();
        child->SetParent(this);
        auto c2 = std::make_unique<sf::CircleShape>(8);
        c2->setFillColor(sf::Color::White);
        auto rend = std::make_unique<aengine::ShapeRenderer>(child, aengine::Game::instance->getWindow(), std::move(c2));
        child->renderer = std::move(rend);
        child->SetPosition(200, 230);

	}

    void Player::Start() {
        this->renderer = std::make_unique<aengine::ShapeRenderer>(this, aengine::Game::instance->getWindow());

        auto shapeRenderer = renderer->to<aengine::ShapeRenderer>();

        shapeRenderer->SetShape(std::make_unique<sf::CircleShape>(30));

        auto circle = shapeRenderer->GetShapeAs<sf::CircleShape>();

        circle->setRadius(30);
        circle->setFillColor(sf::Color(255, 100, 10));
        SetPosition(40, 50);
        circle->setPosition(getPosition().getsf());
    }

	void Player::Update() {
        Gameobject::Update();
        
        aengine::Vectorf delta;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) delta.x = -1 * movementSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) delta.x =  1 * movementSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) delta.y = -1 * movementSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) delta.y =  1 * movementSpeed;

        Translate(delta);

        aengine::Vectorf delta2;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) delta2.x = -1 * movementSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) delta2.x = 1 * movementSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) delta2.y = -1 * movementSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) delta2.y = 1 * movementSpeed;

        getGameobject()->children.at(0)->Translate(delta2);

        aengine::Camera::Translate(delta);
	}

	void Player::Render() {
		Gameobject::Render();
	}
}
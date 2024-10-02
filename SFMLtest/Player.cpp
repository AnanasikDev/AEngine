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
        sf::CircleShape* c2 = new sf::CircleShape();
        c2->setRadius(8);
        c2->setFillColor(sf::Color::White);
        aengine::ShapeRenderer* rend = new aengine::ShapeRenderer(child, aengine::Game::instance->getWindow(), c2);
        child->renderer = rend;
        child->SetPosition(200, 230);

	}

    void Player::Start() {
        // Create a ShapeRenderer and store it in the Renderer pointer
        this->renderer = new aengine::ShapeRenderer(
            this,
            aengine::Game::instance->getWindow()
            );

        // Safely cast the renderer to ShapeRenderer to access the shape property
        aengine::ShapeRenderer* shapeRenderer = static_cast<aengine::ShapeRenderer*>(this->renderer);

        // Create and manage CircleShape with std::make_unique
        shapeRenderer->shape = new sf::CircleShape(30);

        sf::CircleShape* circle = static_cast<sf::CircleShape*>(shapeRenderer->shape);

        // Configure the CircleShape
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
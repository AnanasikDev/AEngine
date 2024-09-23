#include "Player.h"
#include "Gameobject.h"
#include "Renderer.h"
#include "Game.h"
#include <iostream>

namespace agame {

	Player::Player(std::string name) : Gameobject(name) {
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
	}

	void Player::Render() {
		Gameobject::Render();
	}
}
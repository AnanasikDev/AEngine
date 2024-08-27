#include "Player.h"
#include "Gameobject.h"
#include "Game.h"
#include <iostream>

namespace agame {

	Player::Player(std::string name) {
		this->name = name;
	}

    void Player::Init() {
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
        circle->setPosition(position.getsf());
    }

	void Player::Update() {
		//std::cout << "Player update" << std::endl;
        this->Translate(1, 0);
		renderer->Update();
	}

	void Player::Render() {
		Gameobject::Render();
	}
}
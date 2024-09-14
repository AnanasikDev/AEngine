#include "Game.h"
#include "Gameobject.h"
#include "Rigidbody.h"
#include "Physics.h"
#include <iostream>
#include "Time.h"

namespace aengine {

	void Game::InitWindow() {
		this->videoMode.width = 800;
		this->videoMode.height = 600;
		this->defaultColor = sf::Color(220, 220, 255);
		this->window = new sf::RenderWindow(this->videoMode, "My agnma");
	}

	Game::Game() {
		this->window = nullptr;
		instance = this;
		pixelPos = Vectori();
		worldPos = Vectorf();
		Time::Init();
	}

	Game::~Game() {
		delete this->window;
		for (auto obj : gameobjects)
		{
			delete obj;
		}
		delete instance;
		gameobjects.clear();
	}

	sf::RenderWindow* Game::getWindow() const {
		return this->window;
	}

	void Game::FixedUpdate() {
		for (Gameobject* go : gameobjects) {
			if (go->rigidbody != nullptr) {
				go->rigidbody->FixedUpdate();
			}
		}
	}

	void Game::Update() {

		this->PollEvents();

		Time::Update();
		
		for (auto obj : gameobjects) {
			obj->Update();
		}

		/*	TODO: If deltaTime is greater than fixedUpdateInterval
			(On freeze generally when lagging) physics FixedUpdate
			and Update should take that in consideration and 
			scale their changes according to deltaTime.
		*/
		msSinceFixedUpdate += Time::getDeltaTimeMs();
		if (msSinceFixedUpdate >= Physics::fixedUpdateIntervalMs) {
			FixedUpdate();
			msSinceFixedUpdate = 0;
		}

		// get the current mouse position in the window
		pixelPos = Vectori(sf::Mouse::getPosition(*window));

		// convert it to world coordinates
		worldPos = window->mapPixelToCoords(pixelPos.getsf());
	}

	void Game::Render() {
		this->window->clear(this->defaultColor);

		for (auto obj : gameobjects) {
			obj->Render();
		}
		
		this->window->display();
		frame++;
	}

	void Game::Close() {
		this->window->close();
	}

	const bool Game::isRunning() const {
		return this->window->isOpen();
	}

	/// <summary>
	/// Polls SFML events (Window, keyboard, etc.)
	/// </summary>
	void Game::PollEvents() {
		while (window->pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;

			case sf::Event::KeyPressed:

				switch (event.key.code) {

				case sf::Keyboard::Escape:
					window->close();
					break;

				}

				break;
			}
		}
	}

	Game* Game::instance;
}
#include "Game.h"
#include "Gameobject.h"
#include "Rigidbody.h"
#include "Physics.h"
#include <iostream>
#include "Time.h"
#include "Canvas.h"
#include "Input.h"

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
		delete instance;

		// automatically delete all gameobjects
		gameobjects.clear();
	}

	void Game::AddGameobject(Gameobject* gameobject) {
		gameobjects.push_back(std::make_unique<Gameobject>(gameobject));
	}

	sf::RenderWindow* Game::getWindow() const {
		return this->window;
	}

	void Game::Start() {
		for (int i = 0; i < gameobjects.size(); i++) {
			gameobjects[i]->Start();
		}
	}

	void Game::FixedUpdate() {
		for (int i = 0; i < gameobjects.size(); i++) {
			if (gameobjects[i]->rigidbody != nullptr) {
				gameobjects[i]->rigidbody->FixedUpdate();
			}
		}
	}

	void Game::Update() {

		this->PollEvents();

		Time::Update();

		Input::Update();
		
		for (int i = 0; i < gameobjects.size(); i++) {
			gameobjects[i]->Update();
		}

		/*	TODO: If deltaTime is greater than fixedUpdateInterval
			(On freeze generally when lagging) physics FixedUpdate
			and Update should take that in consideration and 
			scale their changes according to deltaTime.
		*/
		if (Time::getFixedDeltaTime() * 1000.f >= Physics::fixedUpdateIntervalMs) {
			FixedUpdate();
			Time::RecordFixedUpdate();
		}

		Canvas::Update();

		// get the current mouse position in the window
		pixelPos = Vectori(sf::Mouse::getPosition(*window));

		// convert it to world coordinates
		worldPos = window->mapPixelToCoords(pixelPos.getsf());
	}

	void Game::Render() {
		this->window->clear(this->defaultColor);

		for (int i = 0; i < gameobjects.size(); i++) {
			gameobjects[i]->Render();
		}

		//Canvas::Render();
		
		this->window->display();
		frame++;
	}

	void Game::Close() {
		this->window->close();
	}

	const bool Game::isRunning() const {
		return this->window->isOpen();
	}

	const bool Game::Contains(Gameobject* gameobject) const {
		for (int i = 0; i < gameobjects.size(); i++) {
			if (gameobjects[i].get() == gameobject)
				return true;
		}
		return false;
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
#include "Game.h"
#include "Gameobject.h"
#include "Rigidbody.h"
#include "Physics.h"
#include <iostream>
#include "Time.h"
#include "Canvas.h"
#include "Input.h"
#include "List.h"
#include "Debug.h"

namespace aengine {

	void Game::initWindow() {
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
		Time::init();
		std::unique_ptr<DebugSink> sink = std::make_unique<Console>();
		Debug::setMethod(std::move(sink));
	}

	Game::~Game() {
		delete this->window;
		delete instance;

		// automatically delete all gameobjects
		gameobjects.clear();
	}

	void Game::addGameobject(Gameobject* gameobject) {
		gameobjects.push_back(std::unique_ptr<Gameobject>(gameobject));
	}

	sf::RenderWindow* Game::getWindow() const {
		return this->window;
	}

	void Game::start() {
		for (int i = 0; i < gameobjects.size(); i++) {
			gameobjects[i]->start();
		}
	}

	void Game::fixedUpdate() {
		for (int i = 0; i < gameobjects.size(); i++) {
			if (gameobjects[i]->rigidbody != nullptr) {
				gameobjects[i]->rigidbody->fixedUpdate();
			}
		}
	}

	void Game::update() {

		this->pollEvents();

		Time::update();

		Input::Update();
		
		for (int i = 0; i < gameobjects.size(); i++) {
			gameobjects[i]->update();
		}

		/*	TODO: If deltaTime is greater than fixedUpdateInterval
			(On freeze generally when lagging) physics FixedUpdate
			and Update should take that in consideration and 
			scale their changes according to deltaTime.
		*/
		if (Time::getFixedDeltaTime() * 1000.f >= Physics::fixedUpdateIntervalMs) {
			fixedUpdate();
			Time::recordFixedUpdate();
		}

		Canvas::update();

		// get the current mouse position in the window
		pixelPos = Vectori(sf::Mouse::getPosition(*window));

		// convert it to world coordinates
		worldPos = window->mapPixelToCoords(pixelPos.getsf());
	}

	void Game::render() {
		this->window->clear(this->defaultColor);

		for (int i = 0; i < gameobjects.size(); i++) {
			gameobjects[i]->render();
		}

		//Canvas::Render();
		
		this->window->display();
		frame++;
	}

	void Game::close() {
		this->window->close();
	}

	const bool Game::isRunning() const {
		return this->window->isOpen();
	}

	const bool Game::contains(Gameobject* gameobject) const {
		for (int i = 0; i < gameobjects.size(); i++) {
			if (gameobjects[i].get() == gameobject)
				return true;
		}
		return false;
	}

	void Game::destroyGameobject(Gameobject* gameobject)
	{
		for (int i = 0; i < gameobjects.size(); i++) {
			if (gameobjects[i].get() == gameobject)
				List::RemoveAt(gameobjects, i);
		}
	}

	/// <summary>
	/// Polls SFML events (Window, keyboard, etc.)
	/// </summary>
	void Game::pollEvents() {
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
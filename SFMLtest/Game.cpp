#include "Game.h"
#include "Gameobject.h"
#include <iostream>

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
	}

	Game::~Game() {
		delete this->window;
		delete instance;
		for (auto obj : gameobjects)
		{
			delete obj;
		}
		gameobjects.clear();
	}

	sf::RenderWindow* Game::getWindow() const {
		return this->window;
	}

	void Game::Update() {

		this->PollEvents();

		// get the current mouse position in the window
		
		pixelPos = Vectori(sf::Mouse::getPosition(*window));

		// convert it to world coordinates
		worldPos = window->mapPixelToCoords(pixelPos.getsf());

		for (auto obj : gameobjects) {
			obj->Update();
		}
	}

	void Game::Render() {
		this->window->clear(this->defaultColor);

		for (auto obj : gameobjects) {
			obj->Render();
		}
		//std::cout << "[" << frame << "]" << " rendering an object " << go.name << std::endl;

		this->window->display();
		frame++;
	}

	void Game::Close() {
		this->window->close();
	}

	const bool Game::isRunning() const {
		return this->window->isOpen();
	}

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
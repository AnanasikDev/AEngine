#include "Game.h"

void Game::InitWindow() {
	this->videoMode.width = 800;
	this->videoMode.height = 600;
	this->defaultColor = sf::Color(220, 220, 255);
	this->window = new sf::RenderWindow(this->videoMode, "My agnma");
}

Game::Game() {
	this->window = nullptr;
}

Game::~Game() {
	delete this->window;
}

void Game::Update() {

	this->PollEvents();
}

void Game::Render() {
	this->window->clear(this->defaultColor);

	this->window->display();
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
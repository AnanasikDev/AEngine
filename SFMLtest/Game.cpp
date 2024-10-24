#include "Engine.h"
#include "Game.h"

namespace aengine {

	void Game::initWindow(float width, float height, const std::string& title) {
		this->videoMode.width = width;
		this->videoMode.height = height;
		this->window = new sf::RenderWindow(this->videoMode, title);
	}

	Game::Game() {
		this->window = nullptr;
		instance = this;
		pixelPos = Vectori();
		worldPos = Vectorf();
		Time::init();
		std::unique_ptr<DebugSink> sink = std::make_unique<Console>();
		Debug::useStyles = true;
		Debug::setDebugSink(std::move(sink));
	}

	Game::~Game() {
		delete this->window;
	}

	sf::RenderWindow* Game::getWindow() const {
		return this->window;
	}

	void Game::update() {
		context()->update();
	}

	void Game::render() {
		context()->render();
	}

	void Game::display() {
		window->display();
	}

	void Game::close() {
		this->window->close();
	}

	const bool Game::isRunning() const {
		return this->window->isOpen();
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
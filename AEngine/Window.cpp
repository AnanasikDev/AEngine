#include "Window.h"

namespace aengine {

	Window::Window(float width, float height, const std::string& title) {
		this->videoMode.width = width;
		this->videoMode.height = height;
		this->window = new sf::RenderWindow(this->videoMode, title);
		instance = this;
		pixelPos = Vectori();
		worldPos = Vectorf();
		Time::init();
		std::unique_ptr<DebugSink> sink = std::make_unique<Console>();
		Debug::useStyles = true;
		Debug::setDebugSink(std::move(sink));
	}

	Window::~Window() {
		delete this->window;
		SceneManager::deleteAllScenes();
	}

	sf::RenderWindow* Window::getWindow() const {
		return this->window;
	}

	void Window::update() {
		this->pollEvents();

		// get the current mouse position in the window
		pixelPos = Vectori(sf::Mouse::getPosition(*window));

		// convert it to world coordinates
		worldPos = window->mapPixelToCoords(pixelPos.getsf());

		context()->update();
	}

	void Window::render() {
		context()->render();
	}

	void Window::display() {
		window->display();
	}

	void Window::close() {
		this->window->close();
	}

	const bool Window::isRunning() const {
		return this->window->isOpen();
	}

	/// <summary>
	/// Polls SFML events (Window, keyboard, etc.)
	/// </summary>
	void Window::pollEvents() {
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

	Window* Window::instance;
	Window* window() {
		return Window::instance;
	}
}
#pragma once


#include <SFML/Graphics.hpp>
#include "Vector.h"
#include <vector>

namespace aengine {

	class Gameobject;
	class Renderer;

	/// <summary>
	/// Class maintaining window, rendering modes, events, engine updates. Handles an SFML RenderWindow object and its settings. Calling current scene update and render functions.
	/// </summary>
	class Window {

	private:
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event event;

	public:
		Vector<int> pixelPos;
		Vectorf worldPos;

		unsigned int frame;
		static Window* instance;

		Window(unsigned int width, unsigned int height, const std::string& title);
		~Window();

		void update();
		void render();
		void display();
		void close();

		Vectorf getSize() const;

		sf::RenderWindow* getWindow() const;

		void pollEvents();

		const bool isRunning() const;
	};

	/// <summary>
	/// Global function to get pointer to the window
	/// </summary>
	Window* window();
}

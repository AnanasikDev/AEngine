#pragma once

#include "Engine.h"
#include <vector>

namespace aengine {

	class Gameobject;
	class Renderer;

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

		Window(float width, float height, const std::string& title);
		~Window();

		void update();
		void render();
		void display();
		void close();

		sf::RenderWindow* getWindow() const;

		void pollEvents();

		const bool isRunning() const;
	};

	/// <summary>
	/// Global function to get pointer to the window
	/// </summary>
	/// <returns></returns>
	Window* window();
}

#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Vector.h"

namespace aengine {

	class Gameobject;
	class Renderer;

	class Game {

	private:
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event event;

	public:
		Vector<int> pixelPos;
		Vectorf worldPos;

		unsigned int frame;
		static Game* instance;

		Game();
		~Game();

		void display();
		void close();


		void initWindow(float width, float height, const std::string& title);
		sf::RenderWindow* getWindow() const;

		void pollEvents();

		const bool isRunning() const;
	};
}
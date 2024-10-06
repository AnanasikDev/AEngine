#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Vector.h"

namespace aengine {

	class Gameobject;

	class Game {

	private:
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event event;
		sf::Color defaultColor;

	public:
		Vector<int> pixelPos;
		Vectorf worldPos;

		unsigned int frame;

		static Game* instance;

		std::vector<std::unique_ptr<Gameobject>> gameobjects;

		Game();
		~Game();

		void initWindow();
		sf::RenderWindow* getWindow() const;

		void start();
		void fixedUpdate();
		void update();
		void render();
		void close();
		void addGameobject(Gameobject* gameobject);

		const bool contains(Gameobject* gameobject) const;
		void destroyGameobject(Gameobject* gameobject);

		void pollEvents();

		const bool isRunning() const;
	};
}
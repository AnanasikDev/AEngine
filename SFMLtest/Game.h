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

		void InitWindow();
		sf::RenderWindow* getWindow() const;

		void Start();
		void FixedUpdate();
		void Update();
		void Render();
		void Close();
		void AddGameobject(Gameobject* gameobject);

		const bool Contains(Gameobject* gameobject) const;
		void DestroyGameobject(Gameobject* gameobject);

		void PollEvents();

		const bool isRunning() const;
	};
}
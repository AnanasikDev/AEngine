#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Game {
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	sf::Color defaultColor;

public:

	Game();
	~Game();

	void InitWindow();

	void Update();
	void Render();
	void Close();

	void PollEvents();

	const bool isRunning() const;
};
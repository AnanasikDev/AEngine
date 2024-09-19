#include "Input.h"
#include "Game.h"

namespace aengine {

	Action<> Input::onLeftMouseButtonPressed;
	Action<> Input::onRightMouseButtonPressed;
	Action<> Input::onMiddleMouseButtonPressed;
	Action<sf::Keyboard::Key> Input::onKeyPressed;
	Action<> Input::onAnyKeyPressed;

	void Input::Update() {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			onLeftMouseButtonPressed.Invoke();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			onRightMouseButtonPressed.Invoke();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			onMiddleMouseButtonPressed.Invoke();

		for (int key = sf::Keyboard::A; key != sf::Keyboard::Z; key++) {

			sf::Keyboard::Key keyName = static_cast<sf::Keyboard::Key>(key);

			if (sf::Keyboard::isKeyPressed(keyName)) {
				onKeyPressed.Invoke(keyName);
				onAnyKeyPressed.Invoke();
			}
		}
	}

	Vectorf Input::getMousePosition() {
		Vectori vi = sf::Mouse::getPosition(*Game::instance->getWindow());
		return Vectorf(vi.x, vi.y);
	}
}
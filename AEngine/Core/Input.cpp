#include "Input.h"
#include "Window.h"

namespace aengine {

	Action<sf::Keyboard::Key> Input::onKeyPressed;
	Action<> Input::onAnyKeyPressed;

	void Input::Update() {

		Input::Mouse::Update();

		for (int key = sf::Keyboard::A; key != sf::Keyboard::Z; key++) {

			sf::Keyboard::Key keyName = static_cast<sf::Keyboard::Key>(key);

			if (sf::Keyboard::isKeyPressed(keyName)) {
				onKeyPressed.Invoke(keyName);
				onAnyKeyPressed.Invoke();
			}
		}
	}

	Vectorf Input::getMousePosition() {
		Vectori vi = sf::Mouse::getPosition(*window()->getWindow());
		return Vectorf(vi.x, vi.y);
	}

	Input::Button::Button(std::function<bool()> func) : function(func) {
	}

	void Input::Button::Update() {
		if (function()) {
			if (!isDown) {
				onPressed.Invoke();
			}

			onHold.Invoke();

			isDown = true;
		}
		else {
			if (isDown) {
				onReleased.Invoke();
			}
			isDown = false;
		}
	}

	Input::Button Input::Mouse::LMB = Button([]() { return sf::Mouse::isButtonPressed(sf::Mouse::Left); });

	Input::Button Input::Mouse::RMB = Button([]() { return sf::Mouse::isButtonPressed(sf::Mouse::Right); });

	Input::Button Input::Mouse::MMB = Button([]() { return sf::Mouse::isButtonPressed(sf::Mouse::Middle); });

	void Input::Mouse::Update() {
		LMB.Update();
		RMB.Update();
		MMB.Update();
	}

	bool Input::isKeyPressed(keyCode key) {
		return sf::Keyboard::isKeyPressed(key);
	}
}
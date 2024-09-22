#include "Input.h"
#include "Game.h"

namespace aengine {

	Action<> Input::onLMBPressed;
	Action<> Input::onLMBReleased;
	Action<> Input::onLMBHold;
	bool Input::isLMBDown;

	Action<> Input::onRMBPressed;
	Action<> Input::onRMBReleased;
	Action<> Input::onRMBHold;
	bool Input::isRMBDown;

	Action<> Input::onMMBPressed;
	Action<> Input::onMMBReleased;
	Action<> Input::onMMBHold;
	bool Input::isMMBDown;


	Action<sf::Keyboard::Key> Input::onKeyPressed;
	Action<> Input::onAnyKeyPressed;

	void Input::Update() {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!isLMBDown) {
				onLMBPressed.Invoke();
			}

			onLMBHold.Invoke();

			isLMBDown = true;
		}
		else 
		{
			if (isLMBDown)
			{
				onLMBReleased.Invoke();
			}
			isLMBDown = false;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (!isRMBDown) {
				onRMBPressed.Invoke();
			}

			onRMBHold.Invoke();

			isRMBDown = true;
		}
		else 
		{
			if (isRMBDown)
			{
				onRMBReleased.Invoke();
			}
			isRMBDown = false;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) 
		{
			if (!isMMBDown) {
				onMMBPressed.Invoke();
			}

			onMMBHold.Invoke();

			isMMBDown = true;
		}
		else 
		{
			if (isMMBDown)
			{
				onMMBReleased.Invoke();
			}
			isMMBDown = false;
		}

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
#pragma once

#include "Vector.h"
#include "Event.h"

using keyCode = sf::Keyboard::Key;

namespace aengine {

	struct Input {

		struct Button {
			Action<> onPressed;
			Action<> onReleased;
			Action<> onHold;
			bool isDown;

			std::function<bool()> function;

			Button(std::function<bool()> func);

			void Update();
		};

		struct Mouse {
			static Button LMB;
			static Button RMB;
			static Button MMB;

			static void Update();
		};
		
		static Action<sf::Keyboard::Key> onKeyPressed;
		static Action<> onAnyKeyPressed;
		
		static Vectorf getMousePosition();

		static bool isKeyPressed(keyCode key);

		static void Update();
	};
}

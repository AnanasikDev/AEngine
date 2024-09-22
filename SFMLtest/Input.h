#pragma once

#include "Vector.h"
#include "Event.h"

namespace aengine {

	class Input {
	public:

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

		static void Update();
	};
}

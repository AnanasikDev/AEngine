#pragma once

#include "Vector.h"
#include "Event.h"

namespace aengine {
	class Input {
	public:
		static Action<> onLeftMouseButtonPressed;
		static Action<> onRightMouseButtonPressed;
		static Action<> onMiddleMouseButtonPressed;
		
		static Action<sf::Keyboard::Key> onKeyPressed;
		static Action<> onAnyKeyPressed;
		
		static Vectorf getMousePosition();

		static void Update();
	};
}
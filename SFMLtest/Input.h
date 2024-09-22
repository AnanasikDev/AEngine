#pragma once

#include "Vector.h"
#include "Event.h"

namespace aengine {
	class Input {
	public:
		static Action<> onLMBPressed;
		static Action<> onLMBReleased;
		static Action<> onLMBHold;
		static bool isLMBDown;
		 
		static Action<> onRMBPressed;
		static Action<> onRMBReleased;
		static Action<> onRMBHold;
		static bool isRMBDown;
		 
		static Action<> onMMBPressed;
		static Action<> onMMBReleased;
		static Action<> onMMBHold;
		static bool isMMBDown;
		
		static Action<sf::Keyboard::Key> onKeyPressed;
		static Action<> onAnyKeyPressed;
		
		static Vectorf getMousePosition();

		static void Update();
	};
}
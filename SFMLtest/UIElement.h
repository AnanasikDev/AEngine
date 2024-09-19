#pragma once

#include "Event.h"
#include "Bounds.h"
#include "Gameobject.h"

namespace aengine {
	class UIElement : Gameobject{
	public:

		Action<> onMouseOver;
		Action<> onMouseDown;
		Action<> onMouseUp;

		Bounds bounds;

		UIElement();
		void Render();
		void Update();
	};
}
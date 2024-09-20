#pragma once

#include "Event.h"
#include "Bounds.h"
#include "Gameobject.h"

namespace aengine {
	class UIElement : Gameobject{
	public:

		Action<> onMouseOver;
		Action<> onMouseDown;
		ActionCallback<> onMouseDownCallback;

		Action<> onMouseUp;

		Bounds bounds;

		UIElement();
		~UIElement();
		void Render();
		void Update();

		Gameobject* getGameobject() override;
	};
}
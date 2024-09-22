#pragma once

#include "Event.h"
#include "Bounds.h"
#include "Gameobject.h"

namespace aengine {
	class UIElement : Gameobject{
	public:

		Action<> onMouseOver;
		backdrop onMouseOverBackdrop;
		Action<> onLMBHold;
		backdrop onLMBHoldBackdrop;
		Action<> onLMBPressed;
		backdrop onLMBPressedBackdrop;
		Action<> onLMBReleased;
		backdrop onLMBReleasedBackdrop;

		Bounds bounds;

		UIElement();
		~UIElement();
		virtual void Render();
		virtual void Update();

		Gameobject* getGameobject() override;

		virtual void OnLMBPressed();
		virtual void OnLMBReleased();
		virtual void OnLMBHold();
	};
}
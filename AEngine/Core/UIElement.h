#pragma once

#include "Event.h"
#include "Bounds.h"
#include "Gameobject.h"

namespace aengine {
	class UIElement : public Gameobject{
	public:

		Action<> onMouseOverEvent;
		backdrop onMouseOverBackdrop;
		Action<> onLMBHoldEvent;
		backdrop onLMBHoldBackdrop;
		Action<> onLMBPressedEvent;
		backdrop onLMBPressedBackdrop;
		Action<> onLMBReleasedEvent;
		backdrop onLMBReleasedBackdrop;

		Bounds bounds;

		UIElement();
		~UIElement();
		virtual void render();
		virtual void update();

		Gameobject* getGameobject() override;

		virtual void onLMBPressed();
		virtual void onLMBReleased();
		virtual void onLMBHold();
		virtual void onMouseOver();
	};
}
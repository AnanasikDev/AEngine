#include "UIElement.h"
#include "Canvas.h"
#include "Input.h"
#include <functional>
#include "TextRenderer.h"

namespace aengine {

	Gameobject* UIElement::getGameobject() {
		return Gameobject::getGameobject();
	}

	UIElement::UIElement() : Gameobject::Gameobject(){
		isAttachedToCamera = true;
		onLMBPressedBackdrop = Input::Mouse::LMB.onPressed.Subscribe( [this]() {
			if (bounds.isPointInside(Input::getMousePosition())) {
				onLMBPressedEvent.Invoke();
				onLMBPressed();
			}
			} );
		onLMBReleasedBackdrop = Input::Mouse::LMB.onReleased.Subscribe( [this]() { 
			if (bounds.isPointInside(Input::getMousePosition())) {
				onLMBReleasedEvent.Invoke();
				onLMBReleased();
			}
			} );
		onLMBHoldBackdrop = Input::Mouse::LMB.onHold.Subscribe( [this]() {
			if (bounds.isPointInside(Input::getMousePosition())) {
				onLMBHoldEvent.Invoke();
				onLMBHold();
			}
			} );
	}

	UIElement::~UIElement() {
		Gameobject::~Gameobject();
		Input::Mouse::LMB.onPressed.Unsubscribe(onLMBPressedBackdrop);
		Input::Mouse::LMB.onReleased.Unsubscribe(onLMBReleasedBackdrop);
		Input::Mouse::LMB.onHold.Unsubscribe(onLMBHoldBackdrop);
	}

	void UIElement::update() {
		Gameobject::update();
	}
		
	void UIElement::render() {
		Gameobject::render();
	}

	void UIElement::onLMBPressed() {
	}

	void UIElement::onLMBReleased() {
	}

	void UIElement::onLMBHold() {
	}
}
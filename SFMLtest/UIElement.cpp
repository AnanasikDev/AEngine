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
		onLMBPressedBackdrop = Input::Mouse::LMB.onPressed.Subscribe( [this]() {
			if (bounds.isPointInside(Input::getMousePosition())) {
				onLMBPressed.Invoke();
				OnLMBPressed();
			}
			} );
		onLMBReleasedBackdrop = Input::Mouse::LMB.onReleased.Subscribe( [this]() { 
			if (bounds.isPointInside(Input::getMousePosition())) {
				onLMBReleased.Invoke();
				OnLMBReleased();
			}
			} );
		onLMBHoldBackdrop = Input::Mouse::LMB.onHold.Subscribe( [this]() {
			if (bounds.isPointInside(Input::getMousePosition())) {
				onLMBHold.Invoke();
				OnLMBHold();
			}
			} );
	}

	UIElement::~UIElement() {
		Gameobject::~Gameobject();
		Input::Mouse::LMB.onPressed.Unsubscribe(onLMBPressedBackdrop);
		Input::Mouse::LMB.onReleased.Unsubscribe(onLMBReleasedBackdrop);
		Input::Mouse::LMB.onHold.Unsubscribe(onLMBHoldBackdrop);
	}

	void UIElement::Update() {
		Gameobject::Update();
	}
		
	void UIElement::Render() {
		Gameobject::Render();
	}

	void UIElement::OnLMBPressed() {
	}

	void UIElement::OnLMBReleased() {
	}

	void UIElement::OnLMBHold() {
	}
}
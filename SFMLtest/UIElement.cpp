#include "UIElement.h"
#include "Canvas.h"
#include "Input.h"
#include <functional>

namespace aengine {

	Gameobject* UIElement::getGameobject() {
		return Gameobject::getGameobject();
	}

	UIElement::UIElement() : Gameobject::Gameobject(){
		Gameobject::Init();

		onLMBPressedBackdrop = Input::onLMBPressed.Subscribe( [this]() { 
			if (bounds.isPointInside(Input::getMousePosition())) {
				onLMBPressed.Invoke();
				OnLMBPressed();
			}
			} );
		onLMBReleasedBackdrop = Input::onLMBReleased.Subscribe( [this]() { 
			if (bounds.isPointInside(Input::getMousePosition())) {
				onLMBReleased.Invoke();
				OnLMBReleased();
			}
			} );
		onLMBHoldBackdrop = Input::onLMBHold.Subscribe( [this]() { 
			if (bounds.isPointInside(Input::getMousePosition())) {
				onLMBHold.Invoke();
				OnLMBHold();
			}
			} );
	}

	UIElement::~UIElement() {
		Gameobject::~Gameobject();
		Input::onLMBPressed.Unsubscribe(onLMBHoldBackdrop);
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
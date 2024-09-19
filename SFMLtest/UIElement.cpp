#include "UIElement.h"
#include "Canvas.h"
#include "Input.h"

namespace aengine {

	Gameobject* UIElement::getGameobject() {
		return Gameobject::getGameobject();
	}

	UIElement::UIElement() : Gameobject::Gameobject(){
		Gameobject::Init();
		Input::onLeftMouseButtonPressed += [this]() { if (bounds.isPointInside(Input::getMousePosition())) onMouseDown.Invoke(); };
	}

	void UIElement::Update() {
		Gameobject::Update();
	}

	void UIElement::Render() {
		Gameobject::Render();
	}
}
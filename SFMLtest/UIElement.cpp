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

		//Input::onLeftMouseButtonPressed.Subscribe(&OnMouseDown);
	}

	UIElement::~UIElement() {
		Gameobject::~Gameobject();
		//Input::onLeftMouseButtonPressed.Unsubscribe(onMouseDownCallback);
	}

	void UIElement::Update() {
		Gameobject::Update();
	}
		
	void UIElement::Render() {
		Gameobject::Render();
	}

	void UIElement::OnMouseDown() {
		if (bounds.isPointInside(Input::getMousePosition()))
			onMouseDown.Invoke();
	}
}
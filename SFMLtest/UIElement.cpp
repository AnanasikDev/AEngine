#include "UIElement.h"
#include "Canvas.h"
#include "Input.h"

namespace aengine {

	Gameobject* UIElement::getGameobject() {
		return Gameobject::getGameobject();
	}

	UIElement::UIElement() : Gameobject::Gameobject(){
		Gameobject::Init();

		onMouseDownCallback = ActionCallback<>(
			[this]()
			{
				if (bounds.isPointInside(Input::getMousePosition()))
					onMouseDown.Invoke();
			});

		Input::onLeftMouseButtonPressed.Subscribe(onMouseDownCallback);
	}

	UIElement::~UIElement() {
		Gameobject::~Gameobject();
		Input::onLeftMouseButtonPressed.Unsubscribe(onMouseDownCallback);
	}

	void UIElement::Update() {
		Gameobject::Update();
	}
		
	void UIElement::Render() {
		Gameobject::Render();
	}
}
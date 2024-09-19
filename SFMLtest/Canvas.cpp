#include "UIElement.h"
#include "Canvas.h"

namespace aengine {

	std::vector<UIElement*> Canvas::elements;

	void Canvas::Render() {
		for (UIElement* element : elements) {
			element->Render();
		}
	}

	void Canvas::Update() {
		for (UIElement* element : elements) {
			element->Update();
		}
	}

	void Canvas::Record(UIElement* element) {
		elements.push_back(element);
	}

	UIElement* Canvas::AddUIElement() {
		auto uielement = new UIElement();
		Record(uielement);
		return uielement;
	}
}
#include "UIElement.h"
#include "Canvas.h"

namespace aengine {

	std::vector<UIElement*> Canvas::elements;

	void Canvas::render() {
		for (UIElement* element : elements) {
			element->render();
		}
	}

	void Canvas::update() {
		for (UIElement* element : elements) {
			element->update();
		}
	}

	void Canvas::record(UIElement* element) {
		elements.push_back(element);
	}

	UIElement* Canvas::addUIElement() {
		auto uielement = new UIElement();
		record(uielement);
		return uielement;
	}
}
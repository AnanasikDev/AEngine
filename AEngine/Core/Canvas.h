#pragma once

#include <vector>

namespace aengine {

	class UIElement;

	class Canvas {
	public:

		static void update();
		static void render();

		static UIElement* addUIElement();

		/// <summary>
		/// Records a new UIElement for updates and rendering
		/// </summary>
		static void record(UIElement* element);
	private:

		static std::vector<UIElement*> elements;
	};
}
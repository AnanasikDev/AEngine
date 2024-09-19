#pragma once

#include <vector>

namespace aengine {

	class UIElement;

	class Canvas {
	public:

		static void Update();
		static void Render();

		static UIElement* AddUIElement();

		/// <summary>
		/// Records a new UIElement for updates and rendering
		/// </summary>
		static void Record(UIElement* element);
	private:

		static std::vector<UIElement*> elements;
	};
}
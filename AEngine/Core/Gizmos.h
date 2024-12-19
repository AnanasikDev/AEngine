#pragma once

#include "Vector.h"
#include "SFML/Graphics/Color.hpp"

namespace aengine {
	class Gizmos {
	public:
		/// <summary>
		/// Draws a 1-pixel-thick line limited by two ends. Operates in screen space.
		/// </summary>
		static void drawSegment(const Vectorf& start, const Vectorf& end, const sf::Color& color = sf::Color::Black);

		/// <summary>
		/// Draws a 1-pixel-thick line limited by two ends. Operates in screen space.
		/// </summary>
		static void drawSegment(const class Line& segment, const sf::Color& color = sf::Color::Black);

		/// <summary>
		/// Draws a 1-pixel-thick line limited by two ends. Operates in screen space. Uses two colors to create a gradient.
		/// </summary>
		static void drawSegment(const class Line& segment, const sf::Color& color1, const sf::Color& color2);

		/// <summary>
		/// Draws a 1-pixel-thick line limited by two ends. Operates in screen space. Uses two colors to create a gradient.
		/// </summary>
		static void drawSegment(const Vectorf& start, const Vectorf& end, const sf::Color& color1, const sf::Color& color2);

		static void drawCircle(const Vectorf& center, float radius, const sf::Color& fillColor = sf::Color::Transparent, const sf::Color& outlineColor = sf::Color::Red, const float outlineThickness = 2);
	};
}

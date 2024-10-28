#pragma once

#include "Vector.h"
#include "SFML/Graphics/Color.hpp"

namespace aengine {
	class Gizmos {
	public:
		static void drawSegment(const Vectorf& start, const Vectorf& end, const sf::Color& color = sf::Color::Black);
		static void drawSegment(const class Line& segment, const sf::Color& color = sf::Color::Black);

		//static void drawCircle(const Vectorf& center, float radius, const sf::Color& color = sf::Color::Black);
	};
}

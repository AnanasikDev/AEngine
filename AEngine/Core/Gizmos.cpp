#include "Gizmos.h"
#include "SFML/Graphics.hpp"
#include "SceneManager.h"
#include "Scene.h"
#include "Window.h"
#include "Line.h"

namespace aengine {
	void Gizmos::drawSegment(const Vectorf& start, const Vectorf& end, const sf::Color& color1, const sf::Color& color2) {
		auto segment = sf::VertexArray(sf::Lines, 2);
		segment[0].color = color1;
		segment[0].position = start.getsf();
		segment[1].color = color2;
		segment[1].position = end.getsf();

		window()->getWindow()->draw(segment);
	}

	void Gizmos::drawSegment(const Line& segment, const sf::Color& color1, const sf::Color& color2) {
		Gizmos::drawSegment(segment.p1, segment.p2, color1, color2);
	}

	void Gizmos::drawSegment(const Vectorf& start, const Vectorf& end, const sf::Color& color) {
		Gizmos::drawSegment(start, end, color, color);
	}

	void Gizmos::drawSegment(const Line& segment, const sf::Color& color) {
		Gizmos::drawSegment(segment.p1, segment.p2, color);
	}

	void Gizmos::drawCircle(const Vectorf& center, float radius, const sf::Color& fillColor, const sf::Color& outlineColor, const float outlineThickness){
		sf::CircleShape shape(radius);
		shape.setOrigin(Vectorf::one.getsf() * radius);
		shape.setPosition(center.getsf());
		shape.setOutlineThickness(outlineThickness);
		shape.setOutlineColor(outlineColor);
		shape.setFillColor(fillColor);

		window()->getWindow()->draw(shape);
	}
}

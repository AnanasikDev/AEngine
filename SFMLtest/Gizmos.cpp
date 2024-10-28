#include "Gizmos.h"
#include "SFML/Graphics.hpp"
#include "SceneManager.h"
#include "Scene.h"
#include "Game.h"
#include "Line.h"

namespace aengine {
	void Gizmos::drawSegment(const Vectorf& start, const Vectorf& end, const sf::Color& color) {
		auto segment = sf::VertexArray(sf::Lines, 2);
		segment[0].color = color;
		segment[0].position = start.getsf();
		segment[1].color = color;
		segment[1].position = end.getsf();

		game()->getWindow()->draw(segment);
	}

	void Gizmos::drawSegment(const Line& segment, const sf::Color& color) {
		Gizmos::drawSegment(segment.p1, segment.p2, color);
	}
}

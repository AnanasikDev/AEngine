#pragma once

#include "Vector.h"
#include <optional>
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/Color.hpp"

namespace aengine {

	class Bounds;

	class Line {
	public:
		Vectorf p1;
		Vectorf p2;
		bool isEmpty = false;

		Line(Vectorf pos1, Vectorf pos2);

		void setPoint1(Vectorf p1, sf::Color color = sf::Color::Black);
		void setPoint2(Vectorf p2, sf::Color color = sf::Color::Black);

		Vectorf getNormal() const;
		inline float getLength() const;

		Vectorf asVector() const;

		static Line lineCircleIntersection(const Line& line, const Vectorf& circleCenter, const float circleRadius);

		static std::optional<Vectorf> getLinesIntersection(const Line& l1, const Line& l2);

		static bool areSegmentsIntersecting(const Line& line1, const Line& line2);

		static std::optional<Vectorf> getSegmentsIntersection(const Line& l1, const Line& l2);

		static Line lineBoundsIntersection(const Line& line, const Bounds& bounds);

		static bool isPointOnLine(const Line& line, const Vectorf& point);

		std::tuple<float, float, float> getABC() const;

		void render(class sf::RenderWindow* window, Vectorf shift = Vectorf::zero, float scale = 1, sf::Color color = sf::Color::Black);

	private:
		sf::VertexArray line;
	};
}

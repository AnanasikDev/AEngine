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

		Line();
		Line(Vectorf pos1, Vectorf pos2);

		void setPoint1(Vectorf p1, sf::Color color = sf::Color::Black);
		void setPoint2(Vectorf p2, sf::Color color = sf::Color::Black);

		static bool linesEqual(const Line& l1, const Line& l2);

		static bool segmentsEqual(const Line& l1, const Line& l2);

		Vectorf getNormal() const;
		inline float getLength() const;

		Vectorf asVector() const;

		bool isPoint() const;

		static Line lineCircleIntersection(const Line& line, const Vectorf& circleCenter, const float circleRadius);

		/// <summary>
		/// <para>
		/// Two lines intersect if they have 1 or more points of intersection
		/// </para>
		/// <para>
		/// Lines do not intersect only if either is true:
		/// </para>
		/// 1. they are parallel
		/// 2. both are defined as points that do not match OR one is indefinite (= point) and doesn't lie on the other line
		/// </summary>
		/// <returns></returns>
		static bool areLinesIntersecting(const Line& line1, const Line& line2);

		static std::optional<Vectorf> getLinesIntersection(const Line& l1, const Line& l2);

		static bool areSegmentsIntersecting(const Line& line1, const Line& line2);

		static std::optional<Vectorf> getSegmentsIntersection(const Line& l1, const Line& l2);

		static bool areSegmentBoundsIntesecting(const Line& line, const Bounds& bounds);

		static std::optional<Line> getSegmentBoundsIntersection(const Line& line, const Bounds& bounds);

		static bool areSegmentLineIntersecting(const Line& segment, const Line& line);
		
		static std::optional<Vectorf> getSegmentLineIntersection(const Line& segment, const Line& line);

		static bool isPointOnSegment(const Line& line, const Vectorf& point);

		static bool isPointOnLine(const Line& line, const Vectorf& point);

		std::tuple<float, float, float> getABC() const;

		void render(class sf::RenderWindow* window, Vectorf shift = Vectorf::zero, float scale = 1, sf::Color color = sf::Color::Black);

	private:
		sf::VertexArray line;
	};

	std::ostream& operator<<(std::ostream& os, const Line& line);
}

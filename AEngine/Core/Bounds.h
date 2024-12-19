#pragma once

#include "Vector.h"
#include <array>

namespace aengine {
	class Bounds {
	public:
		Vectorf minp;
		Vectorf maxp;

		Bounds() = default;
		~Bounds() = default;
		Bounds(Vectorf min, Vectorf max);
		Bounds(float minx, float miny, float maxx, float maxy);

		bool isEmpty() const;
		float getArea() const;
		Vectorf getSize() const;
		Vectorf getCenter() const;

		/// <summary>
		/// Returns all 4 points (vertices) that comprise bounds in clockwise direction: left-up, right-up, right-down, left-down
		/// </summary>
		/// <returns></returns>
		std::array<Vectorf, 4> getPoints() const;
		Bounds setCenterAndSize(Vectorf center, Vectorf size);
		void setLUCornerAndSize(Vectorf minp, Vectorf size);
		void setCenter(Vectorf center);

		static bool areIntersecting(const Bounds& a, const Bounds& b);
		Bounds getIntersectionBounds(const Bounds& other) const;
		static Bounds getIntersectionBounds(const Bounds& a, const Bounds& b);

		std::array<const class Line, 4> getSegments() const;

		bool isPointInside(const Vectorf& point) const;

		Bounds extend(float right, float left, float top, float bottom) const;

		bool operator==(const Bounds& other);
		bool operator!=(const Bounds& other);

		void render(class sf::RenderWindow* window, const Vectorf& shift = Vectorf::zero, const float scale = 1, sf::Color color = sf::Color::Black);

		static Bounds empty;
	};

	std::ostream& operator<<(std::ostream& os, const Bounds& bounds);
}
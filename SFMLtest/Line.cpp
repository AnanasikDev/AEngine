#include "Line.h"
#include "Mathf.h"
#include "SFML/Graphics.hpp"

namespace aengine {
	Line::Line(Vectorf pos1, Vectorf pos2) {
		line = sf::VertexArray(sf::Lines, 2);
		setPoint1(pos1);
		setPoint2(pos2);
	}

	void Line::setPoint1(Vectorf p1, sf::Color color) {
		this->p1 = p1;
		line[0].position = p1.getsf();
		line[0].color = color;
	}

	void Line::setPoint2(Vectorf p2, sf::Color color) {
		this->p2 = p2;
		line[1].position = p2.getsf();
		line[1].color = color;
	}

	float Line::getLength() const {
		return (p1 - p2).getLength();
	}

	Vectorf Line::getNormal() const {
		Vectorf v = p1 - p2;
		return Vectorf(-v.y, v.x);
	}

	Vectorf Line::asVector() const {
		return p2 - p1;
	}

	Line Line::lineCircleIntersection(const Line& line, const Vectorf& circleCenter, const float circleRadius) {
		return Line(Vectorf(), Vectorf()); // NEEDS IMPLEMENTATION
	}

	bool Line::areIntersecting(const Line& line1, const Line& line2) {

		if (Line::isPointOnLine(line1, line2.p1) ||
			Line::isPointOnLine(line1, line2.p2) ||
			Line::isPointOnLine(line2, line1.p1) ||
			Line::isPointOnLine(line2, line1.p2)) return true;

		auto v1 = line1.asVector();
		auto v2 = line2.asVector();

		auto v11 = line2.p1 - line1.p1;
		auto v12 = line2.p2 - line1.p1;

		auto v21 = line1.p1 - line2.p1;
		auto v22 = line1.p2 - line2.p1;

		float c1 = v1.crossProduct(v11);
		float c2 = v1.crossProduct(v12);
		float c3 = v2.crossProduct(v21);
		float c4 = v2.crossProduct(v22);

		//std::cout << c1 << "  " << c2 << "  " << c3 << "  " << c4 << "  " << std::endl;

		if (Mathf::sign(c1) == Mathf::sign(c2)) return false;

		if (Mathf::sign(c3) == Mathf::sign(c4)) return false;

		return true;
	}

	std::optional<Vectorf> Line::getIntersection(const Line& l1, const Line& l2) {
		float a1, b1, c1, a2, b2, c2;
		std::tie(a1, b1, c1) = l1.getABC();
		std::tie(a2, b2, c2) = l2.getABC();


		float det = a1 * b2 - a2 * b1;
		if (det == 0) {
			return std::nullopt; // Lines are parallel
		}
		float x = (b1 * c2 - b2 * c1) / det;
		float y = (a2 * c1 - a1 * c2) / det;
		return Vectorf(x, y);


		std::cout << a1 << " " << b1 << " " << c1 << " " << a2 << " " << b2 << " " << c2 << std::endl;

		Vectorf i;

		

		// check if parallel
		if (a1 / a2 == b1 / b2) {

			// check if identical
			if (c1 == 0 && c2 == 0 || (c1 / c2 == a1 / a2)) { // div by 0
				return (l1.p1 + l1.p2) / 2.f;
			}

			return std::nullopt;
		}
		
		// calculate intersection
		i.y = (c1 / a1 - c2 / a2) / (b2 / a2 - b1 / a1);
		i.x = (-b1 * i.y - c1) / a1;

		return i;
	}

	Line Line::lineBoundsIntersection(const Line& line, const Bounds& bounds) {
		return Line(Vectorf(), Vectorf());
	}

	bool Line::isPointOnLine(const Line& line, const Vectorf& point) {
		if (point == line.p1 || point == line.p2) return true;
		float len = line.getLength();

		return ((line.p1 - point).normalized() == (line.p1 - line.p2) / len &&
			    (line.p2 - point).normalized() == (line.p2 - line.p1) / len);
	}

	std::tuple<float, float, float> Line::getABC() const {
		if (p2.x - p1.x == 0) {
			// no later division, vertical line

			return std::make_tuple<float, float, float>(1 / p1.x, 0, 0);
		}

		if (p2.y - p1.y == 0) {
			// horizontal line

			return std::make_tuple<float, float, float>(0, 1 / p1.y, -1);
		}
		
		const float tan = (p2.y - p1.y) / (p2.x - p1.x);
		const float shift = p1.y - p1.x * tan;

		return std::make_tuple<float, float, float>(-tan, 1, -shift);
	}

	std::optional<Vectorf> Line::oneWay(const Line& l1, const Line& l2, float a1, float b1, float c1, float a2, float b2, float c2) {

		Vectorf i;

		// check if horizontal
		if (a1 == 0) {

			// both are horizontal
			if (a2 == 0) {

				// identical horizontal lines
				if (c1 == c2) {
					return (l1.p1 + l1.p2) / 2.f;
				}
				// parallel horizontal lines, no intersection
				return std::nullopt;
			}

			// second is vertical
			if (b2 == 0) {
				i.y = -c1 / b1;
				i.x = -c2 / a2;
				return i;
			}

			i.x = (c1 / b1 - c2 / b2) / a2;
			i.y = -c1 / b1;

			return i;
		}

		// check if vertical
		if (b1 == 0) {

			// both are vertical
			if (b2 == 0) {

				// identical vertical lines
				if (-c1 / a1 == -c2 / a2) {
					return (l1.p1 + l1.p2) / 2.f;
				}
				return std::nullopt;
			}

			// if second is horizontal
			if (a2 == 0) {
				i.y = -c2 / b2;
				i.x = -c1 / a1;
				return i;
			}

			i.x = (c1 / b1 - c2 / b2) / a2;
			i.y = -c1 / b1;
			return i;
		}
	}

	void Line::render(sf::RenderWindow* window, Vectorf shift, float scale, sf::Color color) {
		std::cout << p1 << p2 << std::endl;
		line[0].position = (p1 * scale + shift).getsf();
		line[1].position = (p2 * scale + shift).getsf();
		line[0].color = color;
		line[1].color = color;
		//line[0].position = shift.getsf();//(Vectorf::fromsf(line[0].position) + shift).getsf();
		window->draw(line);
		line[0].position = p1.getsf();
		line[1].position = p2.getsf();
	}
}

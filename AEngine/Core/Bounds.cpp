#include "Bounds.h"
#include <array>
#include "Line.h"

namespace aengine {

	Bounds Bounds::empty = Bounds();

	Bounds::Bounds(Vectorf lu, Vectorf rd) 
		: minp(lu), maxp(rd) {
	}

	Bounds::Bounds(float minx, float miny, float maxx, float maxy) : minp(Vectorf(minx, miny)), maxp(Vectorf(maxx, maxy)) {
	}

	bool Bounds::operator==(const Bounds& other)
	{
		return this->minp == other.minp && this->maxp == other.maxp;
	}

	bool Bounds::operator!=(const Bounds& other)
	{
		return this->minp != other.minp || this->maxp != other.maxp;
	}

	std::ostream& operator<<(std::ostream& os, const Bounds& bounds) {
		return os << "Bounds(" << bounds.minp << ", " << bounds.maxp << ")";
	}

	float Bounds::getArea() const {
		return (maxp.x - minp.x) * (maxp.y - minp.y);
	}

	bool Bounds::isEmpty() const {
		return getArea() == 0;
	}

	Vectorf Bounds::getSize() const {
		return Vectorf(maxp.x - minp.x, maxp.y - minp.y);
	}

	Vectorf Bounds::getCenter() const {
		return Vectorf((maxp + minp) / 2.f);
	}

	void Bounds::setCenter(Vectorf center) {
		Vectorf size = getSize();
		minp = center - size / 2.f;
		maxp = center + size / 2.f;
	}

	std::array<Vectorf, 4> Bounds::getPoints() const {
		return std::array<Vectorf, 4>{

			minp,
			minp + Vectorf::right * (maxp.x - minp.x),
			maxp,
			minp + Vectorf::down * (maxp.y - minp.y)

		};
	}

	std::array<const Line, 4> Bounds::getSegments() const {
		auto points = getPoints();
		return std::array<const Line, 4>{
			Line(points[0], points[1]),
			Line(points[1], points[2]),
			Line(points[2], points[3]),
			Line(points[3], points[0])
		};
	}

	Bounds Bounds::setCenterAndSize(Vectorf center, Vectorf size) {
		minp = center - size / 2.f;
		maxp = center + size / 2.f;
		return *this;
	}

	void Bounds::setLUCornerAndSize(Vectorf luCorner, Vectorf size) {
		this->minp = luCorner;
		this->maxp = luCorner + size;
	}

	bool Bounds::areIntersecting(const Bounds& a, const Bounds& b) {
		bool isInter = std::max(a.minp.x, b.minp.x) < std::min(a.maxp.x, b.maxp.x) &&
			std::max(a.minp.y, b.minp.y) < std::min(a.maxp.y, b.maxp.y);
		return isInter;
	}

	Bounds Bounds::getIntersectionBounds(const Bounds& a, const Bounds& b) {

		Bounds res;

		if (a.getArea() == 0 || b.getArea() == 0)
			return Bounds::empty;

		if (a.minp.x <= b.minp.x) {
			// b left side is to the right of a left side

			if (b.minp.x >= a.maxp.x) {
				// b has no X intersection with a (b is to the right of a)
				return Bounds::empty;
			}

			else if (a.maxp.x >= b.maxp.x) {
				// b is fully inside of a on X, hence X intersection equals b width
				res.minp.x = b.minp.x;
				res.maxp.x = b.maxp.x;
			}
			else {
				// b left side is inside a, right side is outside
				res.minp.x = b.minp.x;
				res.maxp.x = a.maxp.x;
			}
		}

		if (a.minp.x > b.minp.x) {
			// b left side if to the left of a left side

			if (b.maxp.x <= a.minp.x) {
				// b has no intersection with a (b is to the left of a)
				return Bounds::empty;
			}

			else if (b.maxp.x >= a.maxp.x) {
				// a is completely inside of b on X
				res.minp.x = a.minp.x;
				res.maxp.x = a.maxp.x;
			}

			else {
				// b left side is to the left of a left side, 
				// b right side is also to the left of a right side
				res.minp.x = a.minp.x;
				res.maxp.x = b.maxp.x;
			}
		}



		if (a.minp.y <= b.minp.y) {
			// b top side is to the bottom of a top side

			if (b.minp.y > a.maxp.y) {
				// b has no Y intersection with a (b is to the bottom of a)
				return Bounds::empty;
			}

			else if (a.maxp.y >= b.maxp.y) {
				// b is fully inside of a on Y, hence Y intersection equals b width
				res.minp.y = b.minp.y;
				res.maxp.y = b.maxp.y;
			}
			else {
				// b top side is inside a, bottom side is outside
				res.minp.y = b.minp.y;
				res.maxp.y = a.maxp.y;
			}
		}

		if (a.minp.y > b.minp.y) {
			// b top side if to the top of a top side

			if (b.maxp.y < a.minp.y) {
				// b has no intersection with a (b is to the top of a)
				return Bounds::empty;
			}

			else if (b.maxp.y >= a.maxp.y) {
				// a is completely inside of b on Y
				res.minp.y = a.minp.y;
				res.maxp.y = a.maxp.y;
			}

			else {
				// b top side is to the top of a top side, 
				// b bottom side is also to the top of a bottom side
				res.minp.y = a.minp.y;
				res.maxp.y = b.maxp.y;
			}
		}

		// any of result Bounds sides is 0
		if (res.getArea() == 0)
			return res;

		return res;
	}

	Bounds Bounds::getIntersectionBounds(const Bounds& other) const {
		return getIntersectionBounds(*this, other);
	}

	bool Bounds::isPointInside(const Vectorf& point) const {
		return point.x >= minp.x && point.x <= maxp.x && point.y <= maxp.y && point.y >= minp.y;
	}

	Bounds Bounds::extend(float right, float left, float top, float bottom) const {
		return Bounds(minp.x - left, minp.y - top, maxp.x + right, maxp.y + bottom);
	}

	void Bounds::render(class sf::RenderWindow* window, const Vectorf& shift, const float scale, sf::Color color) {
		auto segments = getSegments();
		for (auto segment : segments) {
			segment.render(window, shift, scale, color);
		}
	}
}
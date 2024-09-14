#include "Bounds.h"

namespace aengine {

	Bounds Bounds::empty = Bounds();

	Bounds::Bounds(Vectorf lu, Vectorf rd) 
		: minp(lu), maxp(rd) {
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

	std::tuple<Vectorf, Vectorf, Vectorf, Vectorf> Bounds::getPoints() const {
		return std::tuple<Vectorf, Vectorf, Vectorf, Vectorf>(

			minp,
			minp + Vectorf::right * (maxp.x - minp.x),
			maxp,
			minp + Vectorf::down * (maxp.y - minp.y)

			);
	}

	void Bounds::setCenterAndSize(Vectorf center, Vectorf size) {
		minp = center - size / 2.f;
		maxp = center + size / 2.f;
	}

	void Bounds::setLUCornerAndSize(Vectorf luCorner, Vectorf size) {
		this->minp = luCorner;
		this->maxp = luCorner + size;
	}

	bool Bounds::areIntersecting(const Bounds& a, const Bounds& b) {
		float width, height;

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

}
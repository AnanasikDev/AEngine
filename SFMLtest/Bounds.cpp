#include "Bounds.h"

namespace aengine {
	Bounds::Bounds(Vectorf lu, Vectorf rd) 
		: minp(lu), maxp(rd) {
	}

	float Bounds::getArea() const {
		return (maxp.x - minp.x) * (maxp.y - minp.y);
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

	Bounds Bounds::getIntersection(const Bounds& a, const Bounds& b) {
		float width, height;

		//bool isInter = std::max(a.minp.x, b.minp.x)
		return Bounds();
	}

	Bounds Bounds::getIntersection(const Bounds& other) const {
		return Bounds::getIntersection(*this, other);
	}

}
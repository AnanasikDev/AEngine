#pragma once

#include "Vector.h"
#include <tuple>

namespace aengine {
	class Bounds {
	public:
		Vectorf minp;
		Vectorf maxp;

		Bounds() = default;
		~Bounds() = default;
		Bounds(Vectorf min, Vectorf max);
		bool isEmpty = false;

		float getArea() const;
		std::tuple<Vectorf, Vectorf, Vectorf, Vectorf> getPoints() const;
		void setCenterAndSize(Vectorf center, Vectorf size);
		void setLUCornerAndSize(Vectorf minp, Vectorf size);

		Bounds getIntersection(const Bounds& other) const;
		static Bounds getIntersection(const Bounds& a, const Bounds& b);
	};
}
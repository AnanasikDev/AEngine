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
		bool isEmpty = true;

		float getArea() const;
		Vectorf getSize() const;
		Vectorf getCenter() const;

		std::tuple<Vectorf, Vectorf, Vectorf, Vectorf> getPoints() const;
		void setCenterAndSize(Vectorf center, Vectorf size);
		void setLUCornerAndSize(Vectorf minp, Vectorf size);
		void setCenter(Vectorf center);

		static bool areIntersecting(const Bounds& a, const Bounds& b);
		Bounds getIntersectionBounds(const Bounds& other) const;
		static Bounds getIntersectionBounds(const Bounds& a, const Bounds& b);

		bool operator==(const Bounds& other);
		bool operator!=(const Bounds& other);

		static Bounds empty;
	};

	std::ostream& operator<<(std::ostream& os, const Bounds& bounds);
}
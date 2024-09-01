#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace aengine {

	template <typename T>

	class Vector {

	public:
		T x;
		T y;

		Vector() {
			this->x = 0;
			this->y = 0;
		}

		Vector(T _x, T _y) {
			this->x = _x;
			this->y = _y;
		}

		Vector(sf::Vector2<T> sfother) {
			this->x = sfother.x;
			this->y = sfother.y;
		}

		Vector<T>& operator+=(const Vector<T>& other) {
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		Vector<T>& operator*=(const float other) {
			this->x *= other;
			this->y *= other;
			return *this;
		}

		Vector<T> operator+(Vector<T> other) {
			return Vector<T>(this->x + other.x, this->y + other.y);
		}

		Vector<T> operator-(Vector<T> other) {
			return Vector<T>(this->x - other.x, this->y - other.y);
		}

		Vector<T> operator*(T fac) {
			return Vector<T>(this->x * fac, this->y * fac);
		}

		Vector<T> operator/(T fac) {
			return Vector<T>(this->x / fac, this->y / fac);
		}

		sf::Vector2<T> getsf() const {
			return sf::Vector2<T>(this->x, this->y);
		}

		float Magnitude() {
			return sqrtf(x * x + y * y);
		}

		void Normalize() {
			float m = Magnitude();
			x /= m;
			y /= m;
		}

		std::string toStr() {
			char buff[50];
			sprintf_s(buff, 50, "(%.4f, %.4f)", (float)(this->x), (float)(this->y));
			return buff;
		}
	};

	typedef Vector<float> Vectorf;
	typedef Vector<int>   Vectori;
}
#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Vectorf {

public:
	float x;
	float y;

	Vectorf() {
		this->x = 0;
		this->y = 0;
	}

	explicit Vectorf(float _x, float _y) {
		this->x = _x;
		this->y = _y;
	}

	Vectorf(const Vectorf& other) {
		this->x = other.x;
		this->y = other.y;
	}

	Vectorf& operator+=(const Vectorf other) {
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	Vectorf operator+(Vectorf other) {
		return Vectorf(this->x + other.x, this->y + other.y);
	}

	Vectorf operator-(Vectorf other) {
		return Vectorf(this->x - other.x, this->y - other.y);
	}

	Vectorf operator*(float fac) {
		return Vectorf(this->x * fac, this->y * fac);
	}

	Vectorf operator/(float fac) {
		return Vectorf(this->x / fac, this->y / fac);
	}

	sf::Vector2<float> getsf() {
		return sf::Vector2<float>(this->x, this->y);
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
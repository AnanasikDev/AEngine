#pragma once

#include <SFML/Graphics.hpp>
#include <string>

template <typename T>

class Vector {

public:
	T x;
	T y;

	Vector(T _x, T _y) {
		this->x = _x;
		this->y = _y;
	}

	Vector<T> operator+(Vector<T> other) {
		return Vector<T>(this->x + other.x, this->y + other.y);
	}

	std::string toStr() {
		char buff[50];
		sprintf_s(buff, 50, "(%.4f, %.4f)", (float)(this->x), (float)(this->y));
		return buff;
	}
};
#pragma once

#include <SFML/Graphics.hpp>


class Collider {
public:
	sf::Vector2f center;

	virtual bool Intersect(Collider& other) = 0;
	virtual bool IsPointInside(sf::Vector2f point) = 0;
};

class CircleCollider : public Collider {
public:
	float radius;

	bool Intersect(Collider& other) override;
};
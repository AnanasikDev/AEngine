#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Component.h"

class Collider : public Component {
public:
	Vectorf center;

	Collider();
	~Collider();

	virtual bool Intersect(Collider& other) = 0;
	virtual bool IsPointInside(sf::Vector2f point) = 0;
};


class CircleCollider : public Collider {
public:
	float radius;

	bool Intersect(Collider& other) override;
};
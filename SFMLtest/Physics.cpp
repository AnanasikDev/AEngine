#include "Physics.h"

bool CircleCollider::Intersect(Collider& other) {
	if (CircleCollider* cc = dynamic_cast<CircleCollider*>(&other)) {
		//return (this->center - other.center).
	}
	return true; /////
}
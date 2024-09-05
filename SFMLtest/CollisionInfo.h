#include "Vector.h"

namespace aengine {
	class CollisionInfo {
	public:
		Vectorf normal;
		Vectorf position;

		CollisionInfo() = default;
		CollisionInfo(Vectorf normal, Vectorf position) {
			this->normal = normal;
			this->position = position;
		}
		~CollisionInfo() = default;
	};
}
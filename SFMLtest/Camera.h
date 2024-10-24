#pragma once

#include "Vector.h"

namespace aengine {

	/// <summary>
	/// Single camera support only.
	/// </summary>
	class Camera {
	private:

		static Vectorf position;
		static class Scene* scene;

	public:

		Camera();

		static void translate(Vectorf delta);
		static void setPosition(Vectorf newPos);
		static Vectorf getPosition();
	};
}

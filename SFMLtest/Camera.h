#pragma once

#include "Vector.h"

namespace aengine {

	/// <summary>
	/// Single camera support only.
	/// </summary>
	class Camera {
	private:

		static Vectorf position;

	public:

		Camera() = default;

		static void Translate(Vectorf delta);
		static void SetPosition(Vectorf newPos);
	};
}

#pragma once

#include "Vector.h"
#include <vector>
#include <memory>
#include <string>

namespace aengine {

	/// <summary>
	/// Single camera support only.
	/// </summary>
	class DllExport Camera {
	private:

		Vectorf position;
		class Scene* scene;
		std::string name;

	public:

		Camera(const std::string& name);
		
		std::string getName() const;
		void translate(Vectorf delta);
		void setPosition(Vectorf newPos);
		Vectorf getPosition() const;
	};
}

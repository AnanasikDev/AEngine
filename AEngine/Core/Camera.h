#pragma once

#include "Vector.h"
#include <vector>
#include <memory>
#include <string>

namespace aengine {

	/// <summary>
	/// Single camera support only.
	/// </summary>
	class Camera {
	private:

		Vectorf cornerPosition;
		class Scene* scene;
		std::string name;
		Vectorf size;

	public:

		Camera(const std::string& name);
		
		std::string getName() const;

		void update();

		void translate(Vectorf delta);
		void setCornerPosition(Vectorf newPos);
		void setCenterPosition(Vectorf newPos);
		Vectorf getCornerPosition() const;
		Vectorf getCenterPosition() const;

		Vectorf worldToScreen(Vectorf worldpos) const;
		Vectorf screenToWorld(Vectorf screenpos) const;

		static Camera* main();
	};

	Camera* mainCamera();
}

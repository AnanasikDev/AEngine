#pragma once

#include "Core/Gameobject.h"

namespace agame{

	class Blob : public aengine::Gameobject {
	public:
		float movementNoiseScale = 0.07f;
		float movementSpeed = 10;

		Blob();

		void update() override;

	};

}

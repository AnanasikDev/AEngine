#pragma once

#include "Core/Gameobject.h"

namespace agame{

	class Blob : public aengine::Gameobject {
	public:

		Blob();

		void update() override;

	};

}

#pragma once

#include "Gameobject.h"
#include "Event.h"

namespace agame {
	class Collectable : public aengine::Gameobject {
	public:
		static unsigned int collected;

		unsigned int onLeftMouseButtonPressedCallback;

		Collectable(std::string name);
		~Collectable();

		void Init() override;
		void Render() override;
		void Update() override;
		void TryCollect();
	};
}
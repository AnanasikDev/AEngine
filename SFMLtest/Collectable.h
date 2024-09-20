#pragma once

#include "Gameobject.h"
#include "Event.h"

namespace agame {
	class Collectable : public aengine::Gameobject {
	public:
		static unsigned int collected;

		Collectable(std::string name);
		~Collectable() = default;

		void Init() override;
		void Render() override;
		void Update() override;
		void TryCollect();
	};
}
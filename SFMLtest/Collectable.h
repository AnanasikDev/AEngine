#pragma once

#include "Gameobject.h"

namespace agame {
	class Collectable : public aengine::Gameobject {
	public:
		Collectable(std::string name);
		~Collectable() = default;

		void Init() override;
		void Render() override;
		void Update() override;
	};
}
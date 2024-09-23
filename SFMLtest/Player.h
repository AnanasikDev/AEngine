#pragma once

#include "Gameobject.h"

namespace agame {
	class Player : public aengine::Gameobject {
	private:
		float movementSpeed = 3;

	public:
		Player(std::string name);

		void Start() override;
		void Update() override;
		void Render() override;
	};
}
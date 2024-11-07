#pragma once

#include "Gameobject.h"

namespace agame {
	class Player : public aengine::Gameobject {
	private:
		float movementSpeed = 3;
		class aengine::Camera* camera;

	public:
		Player(std::string name);

		void start() override;
		void update() override;
		void render() override;
	};
}
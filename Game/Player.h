#pragma once

#include "Core/Gameobject.h"
#include "Core/Camera.h"

namespace agame {
	class Player : public aengine::Gameobject {
	private:
		float movementSpeed = 3;
		aengine::Camera* camera;

	public:
		Player(std::string name);

		void start() override;
		void update() override;
		void render() override;
	};
}
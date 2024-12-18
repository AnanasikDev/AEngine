#pragma once

#include "Core/Gameobject.h"
#include "Core/Camera.h"

namespace agame {
	class Player : public aengine::Gameobject {
	private:
		float movementSpeed = 3;
		float hookDistance = 250;
		aengine::Camera* camera;
		bool isHooked = false;
		Gameobject* hook = nullptr;

	public:
		float radius = 12;

		Player();

		void onTrigger(class aengine::Collider* trigger);
		void onBeforeCollision(class aengine::Collider* collider);

		void start() override;
		void update() override;
		void render() override;
	};
}
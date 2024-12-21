#pragma once

#include "Core/Gameobject.h"
#include "Core/Camera.h"
#include "Trail.h"

namespace agame {
	class Player : public aengine::Gameobject {
	private:
		float movementSpeed = 3;
		float hookDistance = 250;
		float hookForce = 20;
		float blobCollectForce = 5;
		aengine::Camera* camera;

	public:
		DynamicTrail trail;
		bool isHooked = false;
		Gameobject* hook = nullptr;
		float radius = 12;

		Player();

		void onTrigger(class aengine::Collider* trigger);
		void onBeforeCollision(class aengine::Collider* collider);

		void start() override;
		void update() override;
		void render() override;
	};
}
#pragma once

#include "Core/Engine.h"
#include "Bomb.h"

namespace agame {
	Bomb::Bomb() : Gameobject() {
		setRenderer(std::make_unique<aengine::SpriteRenderer>(this, "resources/bomb.png"));
		renderer->setRelativeOrigin(aengine::Vectorf::half);
		setCollider(std::make_unique<aengine::CircleCollider>(this, 30));
	}
}

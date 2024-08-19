#pragma once

#include "Game.h"
#include "Gameobject.h"

namespace agame {
	class Player : public aengine::Gameobject {
	private:

	public:
		using Gameobject::Gameobject;

		void Init() override;
		void Update() override;
		void Render() override;
	};
}
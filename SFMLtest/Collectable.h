#pragma once

#include "Gameobject.h"
#include "Event.h"

namespace agame {
	class Collectable : public aengine::Gameobject {
	public:
		static unsigned int collected;

		aengine::backdrop onLMBDownBackdrop;

		Collectable(std::string name);
		~Collectable();

		void Start() override;
		void Render() override;
		void Update() override;
		void TryCollect();
	};
}
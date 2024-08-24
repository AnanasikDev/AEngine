#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Vector.h"
#include "Renderer.h"

namespace aengine {

	class Gameobject {
	public:
		Vectorf position;
		std::string name;

		//std::unique_ptr<Collider> collider;
		std::unique_ptr<Renderer> renderer;

		Gameobject() {

		}
		Gameobject(std::string name);
		~Gameobject() = default;

		virtual void Init();

		virtual void Render();
		virtual void Update();

		Gameobject(const Gameobject& other) {
			this->position = other.position;
			this->name = other.name;
		}

		Gameobject(Gameobject&& other) noexcept {
			other.swap(*this);
		}

		void swap(Gameobject& other) {
			std::swap(this->position, other.position);
			std::swap(this->name, other.name);
			
			//std::swap(this->bol, other.bol);
		}
	};
}
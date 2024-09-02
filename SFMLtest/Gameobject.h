#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Vector.h"

namespace aengine {

	class Collider;
	class Renderer;
	class Rigidbody;

	class Gameobject {
	public:
		Vectorf position;
		std::string name;

		Collider* collider;
		Renderer* renderer;
		Rigidbody* rigidbody;

		Gameobject() {
			position = Vectorf(0, 0);
			name = "";
		}
		Gameobject(std::string name);
		~Gameobject();

		virtual void Init();

		virtual void Render();
		virtual void Update();

		Gameobject(const Gameobject& other) {
			this->position = other.position;
			this->name = other.name;
		}

		void SetPosition(Vectorf pos) {
			position = pos;
		}

		void SetPosition(float x, float y) {
			position = Vectorf(x, y);
		}

		void Translate(Vectorf delta) {
			position += delta;
		}

		void Translate(float dx, float dy) {
			position += Vectorf(dx, dy);
		}

		void SetScale(float scale);
	};
}
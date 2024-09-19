#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Vector.h"

namespace aengine {

	class Collider;
	class Renderer;
	class Rigidbody;

	class Gameobject {

	private:
		Vectorf position;
	
	public:
		std::string name;

		Collider* collider;
		Renderer* renderer;
		Rigidbody* rigidbody;

		Gameobject();
		Gameobject(std::string name);
		~Gameobject();

		/// <summary>
		/// Registers itself in global list
		/// of instantiates gameobjects. Can
		/// be overriden
		/// </summary>
		virtual void Init();

		/// <summary>
		/// Renders the gameobject. Called after
		/// Update function each frame.
		/// </summary>
		virtual void Render();
		
		/// <summary>
		/// Virtual function, can and should
		/// be overriden by its inheritor.
		/// Called each frame.
		/// </summary>
		virtual void Update();

		Gameobject(const Gameobject& other);

		void SetPosition(Vectorf pos);
		void SetPosition(float x, float y);
		Vectorf getPosition() const;

		void Translate(Vectorf delta);
		void Translate(float dx, float dy);

		void SetScale(float scale);

		virtual Gameobject* getGameobject();
	};
}
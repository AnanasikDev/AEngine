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
		Gameobject* parent;
	
	public:
		std::string name;

		Collider* collider;
		Renderer* renderer;
		Rigidbody* rigidbody;
		bool isAttachedToCamera = false;
		std::vector<Gameobject*> children;

		Gameobject();
		Gameobject(std::string name);
		Gameobject(std::string name, Renderer* renderer);
		Gameobject(std::string name, Renderer* renderer, Collider* collider, Rigidbody* rigidbody);
		~Gameobject();

		/// <summary>
		/// Registers itself in global list
		/// of instantiates gameobjects.
		/// </summary>
		void Register();

		/// <summary>
		/// Called once at the moment of creation of the gameobject. Can be overriden.
		/// </summary>
		virtual void Start();

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

		void SetParent(Gameobject* gameobject);
		Gameobject* getParent() const;
		void ForAllChildrenRecursive(std::function<void(Gameobject*)> func);

		virtual Gameobject* getGameobject();
	};
}
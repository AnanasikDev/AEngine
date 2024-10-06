#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Vector.h"
#include <memory>

#include "Collider.h"
#include "Renderer.h"
#include "Rigidbody.h"

namespace aengine {

	class Gameobject {

	private:
		Vectorf position;
		Gameobject* parent;
	
	public:
		std::string name;

		std::unique_ptr<Collider> collider;
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<Rigidbody> rigidbody;
		bool isAttachedToCamera = false;
		std::vector<Gameobject*> children;

		Gameobject();
		Gameobject(std::string name);
		Gameobject(std::string name, std::unique_ptr<Renderer> renderer);										
		Gameobject(std::string name, std::unique_ptr<Renderer> renderer, std::unique_ptr<Collider> collider, std::unique_ptr<Rigidbody> rigidbody);
		Gameobject(const Gameobject& other);
		~Gameobject() = default;

		void Destroy();

		template <typename T>
		T* SetRenderer(std::unique_ptr<T> _renderer) {
			static_assert(std::is_base_of<Renderer, T>::value, "T must be derived from Renderer");
			this->renderer = std::move(_renderer);
			return static_cast<T*>(this->renderer.get());
		}

		template <typename T>
		T* SetCollider(std::unique_ptr<T> _collider) {
			static_assert(std::is_base_of<Collider, T>::value, "T must be derived from Collider");
			this->collider = std::move(_collider);
			return static_cast<T*>(this->collider.get());
		}

		template <typename T>
		T* SetRigidbody(std::unique_ptr<T> _rigidbody) {
			static_assert(std::is_base_of<Rigidbody, T>::value, "T must be derived from Rigidbody");
			this->rigidbody = std::move(_rigidbody);
			return static_cast<T*>(this->rigidbody.get());
		}

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

		/// <summary>
	/// Sets position of the gameobject to. If includeChildren set to true, all children will be recursively translated too.
	/// </summary>
		void SetPosition(Vectorf pos, bool includeChildren = true);
		void SetPosition(float x, float y, bool includeChildren = true);
		Vectorf getPosition() const;

		/// <summary>
		/// Translates (moves) gameobject by the given delta. If includeChildren set to true, all children will be recursively translated too.
		/// </summary>
		void Translate(Vectorf delta, bool includeChildren = true);

		/// <summary>
		/// Translates (moves) gameobject by the given delta. If includeChildren set to true, all children will be recursively translated too.
		/// </summary>
		void Translate(float dx, float dy, bool includeChildren = true);

		void SetScale(float scale);

		void SetParent(Gameobject* gameobject);
		Gameobject* getParent() const;
		void ForAllChildrenRecursive(std::function<void(Gameobject*)> func);

		virtual Gameobject* getGameobject();
	};
}
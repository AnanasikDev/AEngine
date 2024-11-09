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

		void destroy();

		template <typename T>
		T* setRenderer(std::unique_ptr<T> _renderer) {
			static_assert(std::is_base_of<Renderer, T>::value, "T must be derived from Renderer");
			this->renderer = std::move(_renderer);
			return static_cast<T*>(this->renderer.get());
		}

		template <typename T>
		T* setCollider(std::unique_ptr<T> _collider) {
			static_assert(std::is_base_of<Collider, T>::value, "T must be derived from Collider");
			this->collider = std::move(_collider);
			return static_cast<T*>(this->collider.get());
		}

		template <typename T>
		T* setRigidbody(std::unique_ptr<T> _rigidbody) {
			static_assert(std::is_base_of<Rigidbody, T>::value, "T must be derived from Rigidbody");
			this->rigidbody = std::move(_rigidbody);
			return static_cast<T*>(this->rigidbody.get());
		}

		/// <summary>
		/// Called once at the moment of creation of the gameobject. Can be overriden.
		/// </summary>
		virtual void start();

		/// <summary>
		/// Renders the gameobject. Called after
		/// Update function each frame.
		/// </summary>
		virtual void render();
		
		/// <summary>
		/// Virtual function, can and should
		/// be overriden by its inheritor.
		/// Called each frame.
		/// </summary>
		virtual void update();

		/// <summary>
	/// Sets position of the gameobject to. If includeChildren set to true, all children will be recursively translated too.
	/// </summary>
		void setPosition(Vectorf pos, bool includeChildren = true);
		void setPosition(float x, float y, bool includeChildren = true);
		Vectorf getPosition() const;

		/// <summary>
		/// Translates (moves) gameobject by the given delta. If includeChildren set to true, all children will be recursively translated too.
		/// </summary>
		void translate(Vectorf delta, bool includeChildren = true);

		/// <summary>
		/// Translates (moves) gameobject by the given delta. If includeChildren set to true, all children will be recursively translated too.
		/// </summary>
		void translate(float dx, float dy, bool includeChildren = true);

		void setScale(float scale);

		void setParent(Gameobject* gameobject);
		Gameobject* getParent() const;
		void forAllChildrenRecursive(std::function<void(Gameobject*)> func);

		virtual Gameobject* getGameobject();
	};
}
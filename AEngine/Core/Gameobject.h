#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Vector.h"
#include <memory>

#include "Collider.h"
#include "Renderer.h"
#include "Rigidbody.h"

namespace aengine {

	class Scene* context();

	/// <summary>
	/// Represents an updatable and/or renderable entity. May or may not have a collider, rigidbody and/or renderer (of any type available). Can be attached to another object or camera
	/// </summary>
	class Gameobject {

	private:
		Vectorf worldPosition = Vectorf(0, 0);
		Gameobject* parent;
	
	public:
		std::string name;

		/// <summary>
		/// String tag of the gameobject. Can be empty
		/// </summary>
		std::string tag;

		Vectorf screenPosition = Vectorf(0, 0);

		std::unique_ptr<Collider> collider;
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<Rigidbody> rigidbody;
		bool isAttachedToCamera = false;
		std::vector<Gameobject*> children;
		bool isEnabled = true;

		Gameobject();
		Gameobject(const Gameobject& other);
		~Gameobject() = default;

		static Gameobject* instantiate(const std::string& name, const Vectorf& position = Vectorf::zero);

		template <typename T>
		static T* instantiate(const std::string& name, const Vectorf& position = Vectorf::zero) {
			static_assert(std::is_base_of<Gameobject, T>::value, "T must be derived from Gameobject");
			std::unique_ptr<T> obj = std::make_unique<T>();
			obj->name = name;
			obj->worldPosition = position;
			return static_cast<T*>(context()->addGameobject(std::move(obj)));
		}

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
		/// Sets position of the gameobject to pos. If includeChildren set to true, all children will be recursively affected too.
		/// </summary>
		void setPosition(Vectorf pos, bool includeChildren = true);
		
		/// /// <summary>
		/// Sets position of the gameobject to pos. If includeChildren set to true, all children will be recursively affected too.
		/// </summary>
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
#include "Gameobject.h"
#include "Renderer.h"
#include "Collider.h"
#include "Rigidbody.h"
#include <iostream>
#include "Game.h"
#include "List.h"
#include "Vector.h"

namespace aengine {

	Gameobject::Gameobject() {
		position = Vectorf(0, 0);
		SetParent(nullptr);
		name = "";
		Register();
	}

	Gameobject::Gameobject(std::string name) {
		this->name = name;
		SetParent(nullptr);
		this->position = Vectorf(0, 0);
		Register();
	}

	Gameobject::Gameobject(std::string name, std::unique_ptr<Renderer> renderer) {
		this->name = name;
		SetParent(nullptr);
		this->position = Vectorf(0, 0);
		this->renderer = std::move(renderer);
		Register();
	}

	Gameobject::Gameobject(std::string name, std::unique_ptr<Renderer> renderer, std::unique_ptr<Collider> collider, Rigidbody* rigidbody) {
		this->name = name;
		SetParent(nullptr);
		this->position = Vectorf(0, 0);
		this->renderer = std::move(renderer);
		this->collider = std::move(collider);
		this->rigidbody = rigidbody;
		Register();
	}

	Gameobject::Gameobject(const Gameobject& other) {
		this->position = other.position;
		SetParent(other.getParent());
		this->name = other.name;
		Register();
	}

	Gameobject::~Gameobject() {
		if (parent != nullptr) {
			ForAllChildrenRecursive([this](Gameobject* child) {

				delete child;

				});
			List::Remove(parent->children, this);
		}

		//if (renderer != nullptr) delete renderer;
		//if (collider != nullptr) delete collider;
		if (rigidbody != nullptr) delete rigidbody;

		List::Remove<Gameobject*>(aengine::Game::instance->gameobjects, this);
	}

	void Gameobject::ForAllChildrenRecursive(std::function<void(Gameobject*)> func) {
		for (auto go : children) {
			go->ForAllChildrenRecursive(func);
			func(go);
		}
	}

	void Gameobject::Render() {
		if (renderer != nullptr)
			renderer->Render();
	}

	void Gameobject::Update() {
		if (rigidbody != nullptr) {
			rigidbody->Update();
		}
		
		if (collider != nullptr) {
			collider->Update(this->position);
		}
		
		if (renderer != nullptr) {
			renderer->Update(this->position);
		}
	}

	void Gameobject::Register() {
		aengine::Game::instance->gameobjects.push_back(this);
	}

	void Gameobject::Start() {

	}

	void Gameobject::SetScale(float scale) {
		if (renderer != nullptr) renderer->SetScale(scale);
		if (collider != nullptr) collider->SetScale(scale);
	}

	void Gameobject::SetPosition(Vectorf newPos) {

		ForAllChildrenRecursive([this, newPos](Gameobject* child) {

			child->Translate(newPos - position);

			});

		position = newPos;
		if (collider != nullptr) collider->Update(position);
	}

	void Gameobject::SetPosition(float x, float y) {
		SetPosition(Vectorf(x, y));
	}

	Vectorf Gameobject::getPosition() const {
		return this->position;
	}

	void Gameobject::Translate(Vectorf delta) {
		SetPosition(position + delta);
	}

	void Gameobject::Translate(float dx, float dy) {
		Translate(Vectorf(dx, dy));
	}

	void Gameobject::SetParent(Gameobject* gameobject) {
		this->parent = gameobject;
		
		if (gameobject != nullptr) {
			gameobject->children.push_back(this);

			// if new parent is not null and this gameobject is in rootGameobjects 
			if (List::Contains(Game::instance->rootGameobjects, this)) {
				List::Remove(Game::instance->rootGameobjects, this);
			}
		}
		else {
			// if new parent is null and this gameobject isn't in rootGameobjects 
			if (!List::Contains(Game::instance->rootGameobjects, this)) {
				Game::instance->rootGameobjects.push_back(this);
			}
		}
	}

	Gameobject* Gameobject::getParent() const {
		return this->parent;
	}

	Gameobject* Gameobject::getGameobject() {
		return this;
	}
}
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

	Gameobject::Gameobject(std::string name, std::unique_ptr<Renderer> renderer, std::unique_ptr<Collider> collider, std::unique_ptr<Rigidbody> rigidbody) {

		this->name = name;
		SetParent(nullptr);
		this->position = Vectorf(0, 0);
		this->renderer = std::move(renderer);
		this->collider = std::move(collider);
		this->rigidbody = std::move(rigidbody);
		Register();
	}

	Gameobject::Gameobject(const Gameobject& other){
		this->position = other.position;
		SetParent(other.getParent());
		this->name = other.name;
		Register();
	}

	void Gameobject::Destroy() {

		ForAllChildrenRecursive([this](Gameobject* child) {

			Game::instance->DestroyGameobject(child);

			});
		children.clear();

		if (parent != nullptr) {
			List::Remove(parent->children, this);
		}

		Game::instance->DestroyGameobject(this);
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
		Game::instance->AddGameobject(this);
	}

	void Gameobject::Start() {

	}

	void Gameobject::SetScale(float scale) {
		if (renderer != nullptr) renderer->SetScale(scale);
		if (collider != nullptr) collider->SetScale(scale);
	}

	
	void Gameobject::SetPosition(Vectorf newPos, bool includeChildren) {

		if (includeChildren)
		{
			ForAllChildrenRecursive([this, newPos](Gameobject* child) {

				// shift all children to match the delta
				child->Translate(newPos - position);

				});
		}

		position = newPos;

		// update collider's self position
		if (collider != nullptr) collider->Update(position);
	}

	void Gameobject::SetPosition(float x, float y, bool includeChildren) {
		SetPosition(Vectorf(x, y), includeChildren);
	}

	Vectorf Gameobject::getPosition() const {
		return this->position;
	}

	void Gameobject::Translate(Vectorf delta, bool includeChildren) {
		SetPosition(position + delta, includeChildren);
	}

	void Gameobject::Translate(float dx, float dy, bool includeChildren) {
		Translate(Vectorf(dx, dy), includeChildren);
	}

	void Gameobject::SetParent(Gameobject* gameobject) {
		this->parent = gameobject;
		if (gameobject != nullptr) gameobject->children.push_back(this);
	}

	Gameobject* Gameobject::getParent() const {
		return this->parent;
	}

	Gameobject* Gameobject::getGameobject() {
		return this;
	}
}
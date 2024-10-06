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
		setParent(nullptr);
		name = "";
		Game::instance->addGameobject(this);
	}

	Gameobject::Gameobject(std::string name) {
		this->name = name;
		setParent(nullptr);
		this->position = Vectorf(0, 0);
		Game::instance->addGameobject(this);
	}

	Gameobject::Gameobject(std::string name, std::unique_ptr<Renderer> renderer) {
		this->name = name;
		setParent(nullptr);
		this->position = Vectorf(0, 0);
		this->renderer = std::move(renderer);
		Game::instance->addGameobject(this);
	}

	Gameobject::Gameobject(std::string name, std::unique_ptr<Renderer> renderer, std::unique_ptr<Collider> collider, std::unique_ptr<Rigidbody> rigidbody) {

		this->name = name;
		setParent(nullptr);
		this->position = Vectorf(0, 0);
		this->renderer = std::move(renderer);
		this->collider = std::move(collider);
		this->rigidbody = std::move(rigidbody);
		Game::instance->addGameobject(this);
	}

	Gameobject::Gameobject(const Gameobject& other){
		this->position = other.position;
		setParent(other.getParent());
		this->name = other.name;
		Game::instance->addGameobject(this);
	}

	void Gameobject::destroy() {

		forAllChildrenRecursive([this](Gameobject* child) {

			Game::instance->destroyGameobject(child);

			});
		children.clear();

		if (parent != nullptr) {
			List::remove(parent->children, this);
		}

		Game::instance->destroyGameobject(this);
	}

	void Gameobject::forAllChildrenRecursive(std::function<void(Gameobject*)> func) {
		for (auto go : children) {
			go->forAllChildrenRecursive(func);
			func(go);
		}
	}

	void Gameobject::render() {
		if (renderer != nullptr)
			renderer->render();
	}

	void Gameobject::update() {
		if (rigidbody != nullptr) {
			rigidbody->update();
		}
		
		if (collider != nullptr) {
			collider->update(this->position);
		}
		
		if (renderer != nullptr) {
			renderer->update(this->position);
		}
	}

	void Gameobject::start() {

	}

	void Gameobject::setScale(float scale) {
		if (renderer != nullptr) renderer->setScale(scale);
		if (collider != nullptr) collider->setScale(scale);
	}

	
	void Gameobject::setPosition(Vectorf newPos, bool includeChildren) {

		if (includeChildren)
		{
			forAllChildrenRecursive([this, newPos](Gameobject* child) {

				// shift all children to match the delta
				child->translate(newPos - position);

				});
		}

		position = newPos;

		// update collider's self position
		if (collider != nullptr) collider->update(position);
	}

	void Gameobject::setPosition(float x, float y, bool includeChildren) {
		setPosition(Vectorf(x, y), includeChildren);
	}

	Vectorf Gameobject::getPosition() const {
		return this->position;
	}

	void Gameobject::translate(Vectorf delta, bool includeChildren) {
		setPosition(position + delta, includeChildren);
	}

	void Gameobject::translate(float dx, float dy, bool includeChildren) {
		translate(Vectorf(dx, dy), includeChildren);
	}

	void Gameobject::setParent(Gameobject* gameobject) {
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
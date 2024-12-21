#include "Engine.h"

namespace aengine {

	Gameobject::Gameobject() {
		setParent(nullptr);
		name = "";
		isEnabled = true;
	}

	Gameobject::Gameobject(const Gameobject& other){
		this->worldPosition = other.worldPosition;
		setParent(other.getParent());
		this->name = other.name;
		context()->addGameobject(this);
		isEnabled = other.isEnabled;
	}

	Gameobject* Gameobject::instantiate(const std::string& name, const Vectorf& position) { // change from const ref to value
		std::unique_ptr<Gameobject> obj = std::make_unique<Gameobject>();
		obj->name = name;
		obj->worldPosition = position;
		return context()->addGameobject(std::move(obj));
	}

	void Gameobject::destroy() {

		forAllChildrenRecursive([this](Gameobject* child) {

			context()->destroyGameobject(child);

			});
		children.clear();

		if (parent != nullptr) {
			List::remove(parent->children, this);
		}

		context()->destroyGameobject(this);
	}

	void Gameobject::forAllChildrenRecursive(std::function<void(Gameobject*)> func) {
		for (auto go : children) {
			go->forAllChildrenRecursive(func);
			func(go);
		}
	}

	void Gameobject::render() {
		if (renderer != nullptr) {
			// Camera has just updated screen positions of all gameobjects, now renderers must be updated to new values
			renderer->update(this->screenPosition);
		}

		if (renderer != nullptr) {
			renderer->render();
		}
	}

	void Gameobject::update() {
		if (rigidbody != nullptr) {
			rigidbody->update();
		}
		
		if (collider != nullptr) {
			collider->update(this->worldPosition);
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
				child->translate(newPos - worldPosition);

				});
		}

		worldPosition = newPos;

		// update collider position
		if (collider != nullptr) collider->update(worldPosition);
	}

	void Gameobject::setPosition(float x, float y, bool includeChildren) {
		setPosition(Vectorf(x, y), includeChildren);
	}

	Vectorf Gameobject::getPosition() const {
		return this->worldPosition;
	}

	void Gameobject::translate(Vectorf delta, bool includeChildren) {
		setPosition(worldPosition + delta, includeChildren);
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
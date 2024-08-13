#include "Renderer.h"
#include "Gameobject.h"

void ShapeRenderer::Render() {
	surface->draw(*shape);
}

void ShapeRenderer::Update() {
	shape->setPosition(gameobject->position.getsf());
}

Renderer::Renderer(Gameobject& gameobject, sf::RenderWindow& surface) {
	this->gameobject = std::make_shared<Gameobject>(gameobject);
	this->surface = std::make_shared<sf::RenderWindow>(surface);
}

ShapeRenderer::ShapeRenderer(Gameobject& gameobject, sf::RenderWindow& surface) {
	this->gameobject = std::make_shared<Gameobject>(gameobject);
	this->surface = std::make_shared<sf::RenderWindow>(surface);
}
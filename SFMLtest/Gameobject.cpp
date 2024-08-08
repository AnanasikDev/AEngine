#include "Gameobject.h"
#include <iostream>

Gameobject::Gameobject(std::string name) {
	this->name = name;
	this->position = Vectorf(0, 0);
	//Init();
}

/*
Gameobject::~Gameobject() {

}

void Gameobject::Render() {
	std::cout << "Rendering a gameobject" << std::endl;
}

void Gameobject::Update() {

}

void Gameobject::Init() {

}*/
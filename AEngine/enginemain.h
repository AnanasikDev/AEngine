#pragma once

#include "AENGINE_API.h"
#include <memory>
#include <SFML/Window.hpp>

std::unique_ptr<sf::Window> window;
void DllExport init();
void DllExport show();

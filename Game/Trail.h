#pragma once

#include <functional>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <deque>

class DynamicTrail {
public:
    DynamicTrail(int maxPoints = 20, float vertexDistance = 5.0f);

    void setThicknessFunction(std::function<float(float)> func);
    void setColorFunction(std::function<sf::Color(float)> func);
    void setShiftFunction(std::function<sf::Vector2f(sf::Vector2f)> func);

    void addPoint(const sf::Vector2f& point);
    void generateVertices();

    void render();

private:
    std::deque<sf::Vector2f> worldPoints;
    sf::VertexArray vertices;
    int maxPoints; // Maximum number of points in the trail
    float vertexDistance;
    std::function<float(float)> thicknessFunction;
    std::function<sf::Color(float)> colorFunction;
    std::function<sf::Vector2f(sf::Vector2f)> shiftFunction;

    float distance(const sf::Vector2f& a, const sf::Vector2f& b) const;
};
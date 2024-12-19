#include "Trail.h"
#include "Core/Engine.h"

DynamicTrail::DynamicTrail(int maxPoints, float vertexDistance)
    : maxPoints(maxPoints), vertexDistance(vertexDistance) 
{
    thicknessFunction = [](float val) { return val * 10; };
    colorFunction = [](float val) { return sf::Color::White; };
}

void DynamicTrail::setThicknessFunction(std::function<float(float)> func) {
    thicknessFunction = func;
}

void DynamicTrail::setColorFunction(std::function<sf::Color(float)> func) {
    colorFunction = func;
}

void DynamicTrail::setShiftFunction(std::function<sf::Vector2f(sf::Vector2f)> func) {
    shiftFunction = func;
}

void DynamicTrail::addPoint(const sf::Vector2f& point) {
        // Check if the new point should be added based on vertex distance
    if (!worldPoints.empty() && distance(worldPoints.back(), point) < vertexDistance) {
        return;
    }

    // Add new point to the back
    worldPoints.push_back(point);

    // Remove oldest point if the maximum number of points is exceeded
    if (worldPoints.size() > maxPoints) {
        worldPoints.pop_front();
    }
}

void DynamicTrail::render() {
    if (vertices.getVertexCount() > 0) {
        aengine::window()->getWindow()->draw(vertices);
    }
}

void DynamicTrail::generateVertices() {
    vertices.clear();
    vertices.setPrimitiveType(sf::TriangleStrip);

    if (worldPoints.size() < 2)
        return;

    for (size_t i = 0; i < worldPoints.size(); ++i) {
        sf::Vector2f direction;
        if (i == worldPoints.size() - 1)
            direction = worldPoints[i] - worldPoints[i - 1];
        else
            direction = worldPoints[i + 1] - worldPoints[i];

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;

        // Perpendicular vector for thickness
        sf::Vector2f normal(-direction.y, direction.x);

        // Calculate relative position in the trail (0.0 to 1.0)
        float relativePosition = static_cast<float>(i) / static_cast<float>(worldPoints.size() - 1);

        float thickness = thicknessFunction ? thicknessFunction(relativePosition) : 5.0f;

        sf::Color color = colorFunction(relativePosition);
        sf::Vector2f renderPosition = shiftFunction(worldPoints[i]); // shift points for rendering

        // Add two vertices per point (one on each side of the trail)
        vertices.append(sf::Vertex(renderPosition + normal * thickness, color));
        vertices.append(sf::Vertex(renderPosition - normal * thickness, color));
    }
}

float DynamicTrail::distance(const sf::Vector2f& a, const sf::Vector2f& b) const {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
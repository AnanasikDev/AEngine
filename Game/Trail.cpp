#include "Trail.h"
#include "Core/Engine.h"

DynamicTrail::DynamicTrail(float maxTrailLength, float vertexDistance)
        : maxTrailLength(maxTrailLength), vertexDistance(vertexDistance) {}

void DynamicTrail::setThicknessFunction(std::function<float(float)> func) {
    thicknessFunction = func;
}

void DynamicTrail::addPoint(const sf::Vector2f& point) {
    if (!points.empty() && distance(points.back(), point) < vertexDistance) {
        return; // Skip adding if the distance is too small
    }

    points.push_back(point);

    // Remove points if the trail exceeds the maximum length
    float length = 0.0f;
    for (size_t i = points.size() - 1; i > 0; --i) {
        length += distance(points[i], points[i - 1]);
        if (length > maxTrailLength) {
            points.erase(points.begin(), points.begin() + i - 1);
            break;
        }
    }

    generateVertices();
}

void DynamicTrail::anchorLastAt(const sf::Vector2f& pos) {
    sf::Vector2f delta = points.back() - pos;
    for (int i = 0; i < points.size(); i++) {
        points[i] += delta;
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

    if (points.size() < 2)
        return;

    for (size_t i = 0; i < points.size(); ++i) {
        sf::Vector2f direction;
        if (i == points.size() - 1)
            direction = points[i] - points[i - 1];
        else
            direction = points[i + 1] - points[i];

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;

        // Perpendicular vector for thickness
        sf::Vector2f normal(-direction.y, direction.x);

        // Calculate relative position in the trail (0.0 to 1.0)
        float relativePosition = static_cast<float>(i) / static_cast<float>(points.size() - 1);

        float thickness = thicknessFunction ? thicknessFunction(relativePosition) : 5.0f;

        // Add two vertices per point (one on each side of the trail)
        vertices.append(sf::Vertex(points[i] + normal * thickness, sf::Color::White));
        vertices.append(sf::Vertex(points[i] - normal * thickness, sf::Color::White));
    }
}

float DynamicTrail::distance(const sf::Vector2f& a, const sf::Vector2f& b) const {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
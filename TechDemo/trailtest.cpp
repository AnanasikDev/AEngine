#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include <cmath>

class DynamicTrail {
public:
    DynamicTrail(float maxTrailLength = 200.0f, float vertexDistance = 5.0f)
        : maxTrailLength(maxTrailLength), vertexDistance(vertexDistance) {}

    void setThicknessFunction(std::function<float(float)> func) {
        thicknessFunction = func;
    }

    void addPoint(const sf::Vector2f& point) {
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

    void draw(sf::RenderWindow& window) {
        if (vertices.getVertexCount() > 0) {
            window.draw(vertices);
        }
    }

private:
    std::vector<sf::Vector2f> points;
    sf::VertexArray vertices;
    float maxTrailLength;
    float vertexDistance;
    std::function<float(float)> thicknessFunction;

    void generateVertices() {
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

    float distance(const sf::Vector2f& a, const sf::Vector2f& b) const {
        return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dynamic Trail with Player Controls");

    sf::CircleShape object(10.0f);
    object.setFillColor(sf::Color::Green);
    object.setOrigin(10.0f, 10.0f);
    sf::Vector2f position(400.0f, 300.0f);

    DynamicTrail trail(200.0f, 10.0f);

    // Set a thickness function based on relative position
    trail.setThicknessFunction([](float relativePosition) {
        return relativePosition * 10; // Sinusoidal thickness
        });

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle player controls
        sf::Vector2f velocity;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            velocity.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            velocity.y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocity.x += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocity.x -= 1;
        }

        position += velocity * 0.1f;

        object.setPosition(position);

        // Add position to trail
        trail.addPoint(position);

        window.clear();
        trail.draw(window);
        window.draw(object);
        window.display();
    }

    return 0;
}

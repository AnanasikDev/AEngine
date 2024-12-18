#include <functional>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class DynamicTrail {
public:
    DynamicTrail(float maxTrailLength = 200.0f, float vertexDistance = 5.0f);

    void setThicknessFunction(std::function<float(float)> func);

    void addPoint(const sf::Vector2f& point);

    /// <summary>
    /// Shift all points to make last point be at pos
    /// </summary>
    void anchorLastAt(const sf::Vector2f& pos);

    void render();

private:
    std::vector<sf::Vector2f> points;
    sf::VertexArray vertices;
    float maxTrailLength;
    float vertexDistance;
    std::function<float(float)> thicknessFunction;

    void generateVertices();

    float distance(const sf::Vector2f& a, const sf::Vector2f& b) const;
};
#include "circle.hpp"

Circle::Circle(const sf::Color &color, const sf::Vector2f &pos, const sf::Vector2f &dir, float speed, float radius)
{
    circle.setFillColor(color);
    circle.setOrigin(radius, radius);
    circle.setPosition(pos);
    circle.setRadius(radius);
    const float magnituda = sqrt(dir.x * dir.x + dir.y * dir.y);
    setDir((dir / magnituda) * speed);
}

const sf::Vector2f &Circle::getPosition()
{
    return circle.getPosition();
}

void Circle::setPosition(float x, float y)
{
    circle.setPosition(x, y);
}

void Circle::draw(sf::RenderWindow &window)
{
    window.draw(circle);
}

void Circle::move(const sf::Vector2f &delta)
{
    circle.move(delta);
}

sf::Vector2f &Circle::getDir()
{
    return dir;
}

const float Circle::getRadius()
{
    return circle.getRadius();
}

sf::FloatRect Circle::getGlobalBounds()
{
    return circle.getGlobalBounds();
}

void Circle::setDir(const sf::Vector2f &newDir)
{
    assert(!(newDir.x == 0 && newDir.y == 0));
    this->dir = newDir;
}

bool Circle::isAlive(float deltaTime)
{
    timeLive -= deltaTime;
    return timeLive > 0;
}
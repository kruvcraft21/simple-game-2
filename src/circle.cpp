#include "circle.hpp"

Circle::Circle(const sf::Color &color,const sf::Vector2f& pos, const sf::Vector2f& dir, float radius)
{
    circle.setFillColor(color);
    circle.setOrigin(radius, radius);
    circle.setPosition(pos);
    circle.setRadius(radius);
    setDir(dir);
}

const sf::Vector2f& Circle::getPosition()
{
    return circle.getPosition();
}

void Circle::draw(sf::RenderWindow& window)
{
    window.draw(circle);
}

void Circle::move(const sf::Vector2f& delta)
{
    circle.move(delta * speed);
}

void Circle::DirMulDir(const sf::Vector2f& newDir)
{
    dir = {dir.x * newDir.x, dir.y * newDir.y};
}

sf::Vector2f& Circle::getDir()
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

void Circle::setDir(const sf::Vector2f& newDir)
{
    const float magnituda = sqrt(newDir.x * newDir.x + newDir.y * newDir.y);
    this->dir = newDir / magnituda;
}
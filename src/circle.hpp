#pragma once

#include "SFML/Graphics.hpp"
#include <math.h>
#include <assert.h>

class Circle final
{
private:
    sf::CircleShape circle;
    sf::Vector2f dir = {1, 0};
    float timeLive = 10.f;
    Circle() = delete;

public:
    Circle(const sf::Color &color, const sf::Vector2f &pos, const sf::Vector2f &dir, float speed = 200.f, float radius = 50.f);

    const sf::Vector2f &getPosition() const;
    const float getRadius() const;
    sf::Vector2f &getDir();

    void setPosition(float x, float y);
    void setDir(const sf::Vector2f &newDir);

    void move(const sf::Vector2f &delta);
    void draw(sf::RenderWindow &window);
    bool isAlive(float deltaTime);
};
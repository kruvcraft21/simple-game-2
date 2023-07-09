#pragma once

#include "SFML/Graphics.hpp"
#include <math.h>

class Circle final
{
private:
    sf::CircleShape circle;
    sf::Vector2f dir = {1, 0};
    float speed;
    float timeLive = 10.f;
    Circle() = delete;

public:
    Circle(const sf::Color &color, const sf::Vector2f &pos, const sf::Vector2f &dir, float speed = 200.f, float radius = 50.f);
    const sf::Vector2f &getPosition();
    void move(const sf::Vector2f &delta);
    void draw(sf::RenderWindow &window);
    void DirMulDir(const sf::Vector2f &delta);
    sf::Vector2f &getDir();
    void setDir(const sf::Vector2f &newDir);
    sf::FloatRect getGlobalBounds();
    const float getRadius();
    bool isAlive(float deltaTime);
    void setTmpSpeed(float tmpSpeed);
};
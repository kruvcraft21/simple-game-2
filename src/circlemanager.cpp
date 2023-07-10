#include "circlemanager.hpp"
#include <iostream>

sf::Vector2f CircleManager::getRandomDirection()
{
    uniform_real_distribution<float> dist(MIN_DIRECTION, MAX_DIRECTION);
    return {dist(engine), dist(engine)};
}

float CircleManager::getRandomRadius()
{
    return randomRadius(engine);
}

float CircleManager::getRandomSpeed()
{
    return randomSpeed(engine);
}

sf::Color CircleManager::getRandomColor()
{
    return sf::Color((colors[randomColor(engine)] + colors[randomColor(engine)]) / 2);
}

CircleManager::CircleManager() : engine(unsigned(std::time(nullptr))),
                                 randomRadius(MIN_SIZE_CIRCLE, MAX_SIZE_CIRCLE),
                                 randomSpeed(MIN_SPEED, MAX_SPEED),
                                 randomColor(0, 7)
{
    circles.push_back(Circle(getRandomColor(), {400, 400},
                             getRandomDirection(),
                             getRandomSpeed(),
                             getRandomRadius()));

    circles.push_back(Circle(getRandomColor(), {250, 670},
                             getRandomDirection(),
                             getRandomSpeed(),
                             getRandomRadius()));

    circles.push_back(Circle(getRandomColor(), {479, 235},
                             getRandomDirection(),
                             getRandomSpeed(),
                             getRandomRadius()));

    circles.push_back(Circle(getRandomColor(), {135, 584},
                             getRandomDirection(),
                             getRandomSpeed(),
                             getRandomRadius()));

    circles.push_back(Circle(getRandomColor(), {600, 225},
                             getRandomDirection(),
                             getRandomSpeed(),
                             getRandomRadius()));
}

float dot(sf::Vector2f &v1, sf::Vector2f &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

sf::Vector2f mulVector(const sf::Vector2f &v1, const sf::Vector2f &v2)
{
    return {v1.x * v2.x, v1.y * v2.y};
}

sf::Vector2f delVector(float v1, const sf::Vector2f &v2)
{
    if (v2.x == 0 || v2.y == 0)
        return {0, 0};
    return {v1 / v2.x, v1 / v2.y};
}

// Нагло взято отсюда:
// https://www.jeffreythompson.org/collision-detection/circle-circle.php
bool isCollisionCircles(const sf::Vector2f &pos1, const sf::Vector2f &pos2, float radius1, float radius2)
{
    float distX = pos1.x - pos2.x;
    float distY = pos1.y - pos2.y;
    float distance = sqrt((distX * distX) + (distY * distY));

    // if the distance is less than the sum of the circle's
    // radii, the circles are touching!
    if (distance < radius1 + radius2)
    {
        return true;
    }
    return false;
}

bool isCollisionCircles(const auto &circle1, const auto &circle2, sf::Vector2f &vectorDist)
{
    // get distance between the circle's centers
    // use the Pythagorean Theorem to compute the distance
    const sf::Vector2f &pos1 = circle1->getPosition();
    const sf::Vector2f &pos2 = circle2->getPosition();
    float radius1 = circle1->getRadius();
    float radius2 = circle2->getRadius();
    float distX = pos1.x - pos2.x;
    float distY = pos1.y - pos2.y;
    float distance = sqrt((distX * distX) + (distY * distY));

    // if the distance is less than the sum of the circle's
    // radii, the circles are touching!
    if (distance < radius1 + radius2)
    {
        float dist = (radius1 + radius2) - distance;
        vectorDist.x = (distX / distance) * dist;
        vectorDist.y = (distY / distance) * dist;
        return true;
    }
    return false;
}

sf::Vector2f getElasticCollision(const sf::Vector2f &dir, sf::Vector2f &deltaDir, sf::Vector2f &deltaPos)
{
    return dir - (mulVector(delVector(dot(deltaDir, deltaPos), (mulVector(deltaPos, deltaPos))), deltaPos));
}

void CircleManager::checkElasticCollisionCircles(const auto &circle1)
{
    sf::Vector2f vectorDist = {0, 0};
    for (auto circle2 = circle1 + 1; circle2 != circles.end(); circle2++)
    {
        if (isCollisionCircles(circle1, circle2, vectorDist))
        {
            const auto &dir1 = circle1->getDir();
            const auto &dir2 = circle2->getDir();
            const auto &pos1 = circle1->getPosition();
            const auto &pos2 = circle2->getPosition();
            auto deltaDir1 = dir1 - dir2;
            auto deltaDir2 = dir2 - dir1;
            auto deltaPos1 = pos1 - pos2;
            auto deltaPos2 = pos2 - pos1;

            // Устанавливаем новый вектор движения
            circle1->setDir(getElasticCollision(dir1, deltaDir1, deltaPos1));
            circle2->setDir(getElasticCollision(dir2, deltaDir2, deltaPos2));

            // Устанавливаем позицию соприкосновения, чтобы шары не слипались
            circle1->setPosition(pos1.x + vectorDist.x, pos1.y + vectorDist.y);
            circle2->setPosition(pos2.x - vectorDist.x, pos2.y - vectorDist.y);
        }
    }
}

void CircleManager::update(sf::RenderWindow &window)
{
    const float deltaTime = clock.restart().asSeconds();
    if (deltaTime < 0.1f)
    {
        for (auto circle = circles.begin(); circle != circles.end();)
        {
            auto &pos = circle->getPosition();
            const float radius = circle->getRadius();
            auto &dir = circle->getDir();

            checkElasticCollisionCircles(circle);

            if (pos.x + radius >= WINDOW_WIDTH)
            {
                dir.x *= -1;
                circle->setPosition(WINDOW_WIDTH - radius, pos.y);
            }
            if (pos.x - radius < 0)
            {
                dir.x *= -1;
                circle->setPosition(radius, pos.y);
            }

            if (pos.y + radius >= WINDOW_HEIGHT)
            {
                dir.y *= -1;
                circle->setPosition(pos.x, WINDOW_HEIGHT - radius);
            }
            if (pos.y - radius < 0)
            {
                dir.y *= -1;
                circle->setPosition(pos.x, radius);
            }

            circle->move(dir * deltaTime);
            circle->draw(window);

            if (circle->isAlive(deltaTime))
            {
                circle++;
            }
            else
            {
                circle = circles.erase(circle);
            }
        }

        tryAddCircle();
    }
}

void CircleManager::tryAddCircle()
{
    while (!mouseClicks.empty())
    {
        auto &pos = mouseClicks.front();
        float radius = getRandomRadius();

        bool isCollision = false;

        for (auto &circle : circles)
        {
            isCollision |= isCollisionCircles(pos, circle.getPosition(), radius, circle.getRadius());
        }

        if (!isCollision)
        {
            circles.push_back(Circle(getRandomColor(), pos, getRandomDirection(), getRandomSpeed(), radius));
        }

        mouseClicks.pop();
    }
}

void CircleManager::addClickPos(int x, int y)
{
    mouseClicks.push({static_cast<float>(x), static_cast<float>(y)});
}
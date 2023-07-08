#include "circlemanager.hpp"
#include <iostream>

sf::Vector2f getRandomDirection(mt19937 engine)
{
    uniform_real_distribution<float> dist(MIN_DIRECTION, MAX_DIRECTION);
    return {dist(engine), dist(engine)};
}

CircleManager::CircleManager()
{
    const unsigned seed = unsigned(std::time(nullptr));
    engine.seed(seed);

    uniform_int_distribution<int> color(0, 7);

    uniform_real_distribution<float> sizeCircle(MIN_SIZE_CIRCLE,
                                                MAX_SIZE_CIRCLE);

    uniform_real_distribution<float> speedGenerator(MIN_SPEED, MAX_SPEED);

    sf::Color c1((colors[color(engine)] + colors[color(engine)]) / 2);
    circles.push_back(Circle(c1, {400, 400},
                             getRandomDirection(engine),
                             speedGenerator(engine),
                             sizeCircle(engine)));

    sf::Color c2((colors[color(engine)] + colors[color(engine)]) / 2);
    circles.push_back(Circle(c2, {250, 670},
                             getRandomDirection(engine),
                             speedGenerator(engine),
                             sizeCircle(engine)));

    sf::Color c3((colors[color(engine)] + colors[color(engine)]) / 2);
    circles.push_back(Circle(c3, {479, 235},
                             getRandomDirection(engine),
                             speedGenerator(engine),
                             sizeCircle(engine)));

    sf::Color c4((colors[color(engine)] + colors[color(engine)]) / 2);
    circles.push_back(Circle(c4, {135, 584},
                             getRandomDirection(engine),
                             speedGenerator(engine),
                             sizeCircle(engine)));

    sf::Color c5((colors[color(engine)] + colors[color(engine)]) / 2);
    circles.push_back(Circle(c5, {600, 225},
                             getRandomDirection(engine),
                             speedGenerator(engine),
                             sizeCircle(engine)));
}

float dot(sf::Vector2f &v1, sf::Vector2f &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

sf::Vector2f mulVector(const sf::Vector2f &v1, const sf::Vector2f &v2)
{
    return {v1.x * v2.x, v1.y * v2.y};
}

// Нагло взято отсюда:
// https://www.jeffreythompson.org/collision-detection/circle-circle.php
bool isCollisionCircles(const auto &circle1, const auto &circle2)
{
    // get distance between the circle's centers
    // use the Pythagorean Theorem to compute the distance
    const sf::Vector2f &pos1 = circle1->getPosition();
    const sf::Vector2f &pos2 = circle2->getPosition();
    float distX = pos1.x - pos2.x;
    float distY = pos1.y - pos2.y;
    float distance = sqrt((distX * distX) + (distY * distY));

    // if the distance is less than the sum of the circle's
    // radii, the circles are touching!
    if (distance <= circle1->getRadius() + circle2->getRadius())
    {
        return true;
    }
    return false;
}

sf::Vector2f getElasticCollision(const sf::Vector2f &dir, sf::Vector2f &deltaDir, sf::Vector2f &deltaPos)
{
    return dir - (mulVector(dot(deltaDir, deltaPos) * (mulVector(deltaPos, deltaPos) * powf(1.f, -1)), deltaPos));
}

void CircleManager::checkElasticCollisionCircles(const auto &circle1)
{
    for (auto circle2 = circle1 + 1; circle2 != circles.end(); circle2++)
    {
        if (isCollisionCircles(circle1, circle2))
        {
            const auto &dir1 = circle1->getDir();
            const auto &dir2 = circle2->getDir();
            const auto &pos1 = circle1->getPosition();
            const auto &pos2 = circle2->getPosition();
            auto deltaDir1 = dir1 - dir2;
            auto deltaDir2 = dir2 - dir1;
            auto deltaPos1 = pos1 - pos2;
            auto deltaPos2 = pos2 - pos1;

            circle1->setDir(getElasticCollision(dir1, deltaDir1, deltaPos1));

            circle2->setDir(getElasticCollision(dir2, deltaDir2, deltaPos2));
        }
    }
}

void CircleManager::update(sf::RenderWindow &window)
{
    const float deltaTime = clock.restart().asSeconds();
    if (deltaTime < 0.1f)
    {
        for (auto circle = circles.begin(); circle != circles.end(); circle++)
        {
            auto &pos = circle->getPosition();
            const float radius = circle->getRadius();
            const auto &dir = circle->getDir();
            circle->move(dir * deltaTime);
            circle->draw(window);

            checkElasticCollisionCircles(circle);

            if (pos.x + radius >= WINDOW_WIDTH || pos.x - radius < 0)
            {
                circle->DirMulDir({-1, 1});
            }
            if (pos.y + radius >= WINDOW_HEIGHT || pos.y - radius < 0)
            {
                circle->DirMulDir({1, -1});
            }
        }
    }
}
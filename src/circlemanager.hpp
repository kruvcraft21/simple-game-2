#pragma once

#include "circle.hpp"
#include "SFML/System.hpp"
#include <vector>

using namespace std;

constexpr unsigned int WINDOW_HEIGHT = 800;
constexpr unsigned int WINDOW_WIDTH = 800;

class CircleManager final
{
private:
    vector<Circle> circles;
    sf::Clock clock;
    CircleManager();
    void checkElasticCollisionCircles(const auto &circle1);

public:
    CircleManager(const CircleManager&) = delete;
    CircleManager& operator=(const CircleManager&) = delete;
    static CircleManager& getIstance() 
    {
        static CircleManager instance;
        return instance;
    }
    void update(sf::RenderWindow& window);
};
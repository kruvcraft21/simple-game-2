#pragma once

#include "circle.hpp"
#include "mathutils.hpp"
#include "SFML/System.hpp"
#include <vector>
#include <random>
#include <ctime>
#include <queue>

using namespace std;

constexpr float TOLERANCE_DELTA_TIME = 0.1f;

constexpr unsigned int WINDOW_HEIGHT = 800;
constexpr unsigned int WINDOW_WIDTH = 800;

constexpr int MIN_DIRECTION = -1000;
constexpr int MAX_DIRECTION = 1000;

constexpr float MAX_SPEED = 200.f;
constexpr float MIN_SPEED = 100.f;

constexpr float MIN_SIZE_CIRCLE = 5.f;
constexpr float MAX_SIZE_CIRCLE = 50.f;

constexpr unsigned int colors[]{
    0x42AAFFff, // Голубой
    0xFF2B2Bff, // Оранжево-красный Крайола
    0xFFDB58ff, // Горчичный
    0xD71868ff, // Грузинский розовый
    0x7CFC00ff, // Зеленая лужайка
    0xF5E6CBff, // Зеленовато-белый
    0xFF4D00ff, // Киноварь
    0x9A366Bff  // Насыщенный красно-пурпурный
};

class CircleManager final
{
private:
    queue<sf::Vector2f> mouseClicks;
    vector<Circle> circles;
    sf::Clock clock;
    mt19937 engine;
    uniform_real_distribution<float> randomRadius;
    uniform_real_distribution<float> randomSpeed;
    uniform_int_distribution<int> randomColor;

private:
    CircleManager();
    void checkElasticCollisionCircles(const auto &circle1);
    void checkWallCollision(const auto &circle);
    void tryAddCircle();
    float getRandomRadius();
    float getRandomSpeed();
    sf::Vector2f getRandomDirection();
    sf::Color getRandomColor();

public:
    void addClickPos(int x, int y);
    CircleManager(const CircleManager &) = delete;
    CircleManager &operator=(const CircleManager &) = delete;
    static CircleManager &getIstance()
    {
        static CircleManager instance;
        return instance;
    }
    void update(sf::RenderWindow &window);
};
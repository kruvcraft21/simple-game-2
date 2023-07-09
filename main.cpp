#include <iostream>
#include "SFML/Graphics.hpp"
#include "src/circlemanager.hpp"

void pollEvent(sf::RenderWindow &window, CircleManager &circleManager)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::EventType::Closed:
            window.close();
            break;
        case sf::Event::EventType::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Button::Left)
            {
                circleManager.addClickPos(event.mouseButton.x, event.mouseButton.y);
            }
        default:
            break;
        }
    }
}

#ifdef ISWIN32
int WinMain(void *)
#else
int main(void *)
#endif
{
    std::cout << "Hello, from simple-game-2!\n";

    sf::ContextSettings setting;
    setting.antialiasingLevel = 8;
    sf::RenderWindow window({WINDOW_WIDTH, WINDOW_HEIGHT}, "Circles", sf::Style::Default, setting);
    window.setFramerateLimit(60);
    auto &circles = CircleManager::getIstance();

    while (window.isOpen())
    {

        pollEvent(window, circles);
        window.clear();
        circles.update(window);
        window.display();
    }
}

#include <iostream>
#include "SFML/Graphics.hpp"
#include "src/circlemanager.hpp"

#ifdef ISWIN32
int WinMain(void*)
#else
int main(void*)
#endif
{
    std::cout << "Hello, from simple-game-2!\n";

    sf::ContextSettings setting;
    setting.antialiasingLevel = 8;
    sf::RenderWindow window({WINDOW_WIDTH, WINDOW_HEIGHT}, "Circles", sf::Style::Default, setting);
    window.setFramerateLimit(60);
    auto& circles = CircleManager::getIstance();

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();
        circles.update(window);
        window.display();
    }
}

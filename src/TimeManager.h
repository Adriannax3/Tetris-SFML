#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class TimeManager
{
    sf::Font font;
    sf::Text text;

    int time;

    std::jthread timer;

    bool running;

public:
    TimeManager()
    {
        if (!font.loadFromFile("./FONT/VT323-Regular.ttf"))
        {
            std::cerr << "nie udalo sie zaladowac czcionki - timeManager" << std::endl;
        }
        this->time = 0;
        this->running = false;
    }
    ~TimeManager()
    {
        this->stop();
    }

    void start();
    void update();
    void draw(sf::RenderWindow * window);
    void stop();
    std::string getTime();
};

#endif
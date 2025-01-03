#ifndef HOWTOPLAYSTATE_H
#define HOWTOPLAYSTATE_H

#include "GameState.h"

class Window;

class HowToPlayState :
    public State
{
    sf::RectangleShape background;
    sf::Texture texture;
    sf::Sprite sprite;

    std::map<std::string, Button*> buttons;

public:
    HowToPlayState(sf::RenderWindow* w, std::stack<State*>* states);
    ~HowToPlayState();
    void initButtons();
    void updateButtons();
    void updateMousePos();
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
    void update(const float& dt);
    void endState();
};

#endif
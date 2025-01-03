#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "HowToPlayState.h"
#include "RankingState.h"

class Window;

class MainMenuState :
    public State
{
    sf::RectangleShape background;
    sf::Texture texture;
    sf::Sprite sprite;
    std::map<std::string, Button*> buttons;

public:
    MainMenuState(sf::RenderWindow* w, std::stack<State*>* states);
    ~MainMenuState();
    void initButtons();
    void updateButtons();
    void updateMousePos();
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
    void update(const float& dt);
    void endState();
};

#endif
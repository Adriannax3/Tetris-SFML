#pragma once
#include "State.h"
#include "ScoreManager.h"
#include "MainMenuState.h"

class EndGameState :
    public State
{
    ScoreManager scoreManager;
    sf::RectangleShape background;

    std::map<std::string, Button*> buttons;

    sf::RectangleShape bgText;
    sf::Text txtNick;
    sf::Text txtError;
    std::string nick;
    std::string error;
    bool isResultSaved;

    sf::Texture texture;
    sf::Sprite sprite;

public:
    EndGameState(sf::RenderWindow* window, std::stack<State*>* states, ScoreManager sc);
    ~EndGameState() {}
    void drawResults();
    void render(sf::RenderTarget* target);
    void initButtons();
    void renderButtons(sf::RenderTarget* target = nullptr);
    void updateButtons();
    void saveScore();
    void update(const float& dt);
    std::string chooseComment();
    sf::Color chooseColor();
    void updateInputs();
    void saved();
    void chooseEmoji(sf::RenderTarget * target);
};


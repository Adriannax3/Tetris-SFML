#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "RankingState.h"
#include "GameManager.h"

class GameState :
    public State
{
    sf::RectangleShape background;
    GameManager gameManager = NULL;
    

public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states);
    ~GameState();

    void update(const float& dt);
    void render(sf::RenderTarget* window = nullptr);
    void endState();
};

#endif

#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
	int width = 1200;
	int height = 800;

	sf::RenderWindow* window;
	sf::Event Event;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

public:
	Game();
	~Game();
	void updateSFMLEvents();
	void render();
	void update();
	void run();
	void updateDt();
	void initStates();
};

#endif
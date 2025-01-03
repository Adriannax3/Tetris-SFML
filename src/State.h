#ifndef STATE_H
#define STATE_H

#include "Button.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stack>
#include <map>

class State
{
protected:
	sf::RenderWindow* window;

	std::stack<State*>* states;
	bool isEnd;
	sf::Vector2f mousePosition;
	sf::Font font;

public:
	State(sf::RenderWindow* window, std::stack<State*>* states);
	~State();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* window = nullptr);
	virtual void checkForEnd();
	const bool& getEnd() const;
	virtual void endState();
	virtual void updateMousePosition();
};

#endif
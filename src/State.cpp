#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	this->window = window;
	this->states = states;
	this->isEnd = false;

	if (!font.loadFromFile("./FONT/VT323-Regular.ttf"))
	{
		std::cerr << "nie udalo sie zaladowac czcionki" << std::endl;
	}
}

State::~State()
{
}

void State::update(const float& dt)
{
}

void State::render(sf::RenderTarget* window)
{
}

void State::checkForEnd()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		this->isEnd = true;
	}
}

void State::endState()
{
}

void State::updateMousePosition()
{
	this->mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

const bool& State::getEnd() const
{
	return this->isEnd;
}

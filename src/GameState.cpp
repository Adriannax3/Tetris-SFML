#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states), gameManager(this->window)
{
	gameManager.setEndGame(false);
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Black);
}

GameState::~GameState()
{
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->checkForEnd();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
	}
	if (!this->gameManager.getEndGame()) {
		gameManager.initGame();
	}
	if (this->gameManager.getEndGame()) {
		endState();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	this->window->draw(background);
}

void GameState::endState()
{
	this->isEnd = true;
	this->states->pop();
	this->states->push(new EndGameState(this->window, this->states, this->gameManager.getResults()));
}
 
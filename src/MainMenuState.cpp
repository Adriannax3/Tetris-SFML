#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color(39, 60, 84));
	this->initButtons();

	if (!texture.loadFromFile("./assets/tetris.png"))
	{
		std::cerr << "Failed to load texture" << std::endl;
	}
	this->sprite.setTexture(texture);
	this->sprite.setPosition(sf::Vector2f(200, 50));

}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePosition();
	this->checkForEnd();
	this->updateButtons();
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	this->renderButtons(target);
	target->draw(this->sprite);
}

void MainMenuState::initButtons()
{
	this->buttons["START"] = new Button((this->window->getSize().x/2 - 200), 270, 400, 100, &this->font, "START",
		sf::Color(154, 202, 209), sf::Color(112, 170, 178), sf::Color(173, 216, 230), 75);

	this->buttons["HTP"] = new Button((this->window->getSize().x / 2 - 200), 400, 400, 100, &this->font, "HOW TO PLAY?",
		sf::Color(154, 202, 209), sf::Color(112, 170, 178), sf::Color(173, 216, 230), 75);

	this->buttons["RANK"] = new Button((this->window->getSize().x / 2 - 200), 530, 400, 100, &this->font, "RANKING",
		sf::Color(154, 202, 209), sf::Color(112, 170, 178), sf::Color(173, 216, 230), 75);

	this->buttons["EXIT"] = new Button((this->window->getSize().x / 2 - 200), 660, 400, 100, &this->font, "EXIT",
		sf::Color(154, 202, 209), sf::Color(112, 170, 178), sf::Color(173, 216, 230), 75);

}

void MainMenuState::updateButtons()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != buttons.end(); ++it) {
		it->second->update(this->mousePosition);
	}

	if (this->buttons["START"]->isPressed()) {
		this->isEnd = true;
		this->states->pop();
		this->states->push(new GameState(this->window, this->states));
	}

	if (this->buttons["HTP"]->isPressed()) {
		this->isEnd = true;
		this->states->pop();
		this->states->push(new HowToPlayState(this->window, this->states));
	}

	if (this->buttons["RANK"]->isPressed()) {
		this->isEnd = true;
		this->states->pop();
		this->states->push(new RankingState(this->window, this->states));
	}

	if (this->buttons["EXIT"]->isPressed()) {
		this->isEnd = true;
	}
}


void MainMenuState::endState()
{
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != buttons.end(); ++it) {
		it->second->render(target);
	}
}

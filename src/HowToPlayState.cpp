#include "HowToPlayState.h"

HowToPlayState::HowToPlayState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color(39, 60, 84));
	this->initButtons();

	if (!texture.loadFromFile("./assets/htp.png"))
	{
		std::cerr << "Failed to load texture" << std::endl;
	}
	this->sprite.setTexture(texture);
	this->sprite.setPosition(sf::Vector2f(0, 0));
	sprite.setScale(0.95f, 0.95f);
}

HowToPlayState::~HowToPlayState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
	}
}

void HowToPlayState::update(const float& dt)
{
	this->updateMousePosition();
	this->checkForEnd();
	this->updateButtons();

}

void HowToPlayState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(this->sprite);
	this->renderButtons(target);
}

void HowToPlayState::initButtons()
{
	this->buttons["OK"] = new Button((this->window->getSize().x / 2 - 200), (this->window->getSize().y - 120), 400, 100, &this->font, "OK",
		sf::Color(154, 202, 209), sf::Color(112, 170, 178), sf::Color(173, 216, 230), 75);
}

void HowToPlayState::updateButtons()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != buttons.end(); ++it) {
		it->second->update(this->mousePosition);
	}

	if (this->buttons["OK"]->isPressed()) {
		this->states->push(new GameState(this->window, this->states));
	}
}


void HowToPlayState::endState()
{
}

void HowToPlayState::renderButtons(sf::RenderTarget* target)
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != buttons.end(); ++it) {
		it->second->render(target);
	}
}

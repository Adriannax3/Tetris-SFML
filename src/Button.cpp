#include "Button.h"
#include <iostream>

Button::Button(int posX, int posY, int width, int height, 
	sf::Font* font, std::string txt, 
	sf::Color dC, sf::Color hC, sf::Color aC, int fontSize)
{
	this->btn_state = DEFAULT;
	this->shape.setPosition(sf::Vector2f(posX, posY));
	this->shape.setSize(sf::Vector2f(width, height));
	this->font = font;
	this->txt.setFont(*this->font);
	this->txt.setString(txt);
	this->txt.setFillColor(sf::Color::White);
	this->txt.setCharacterSize(fontSize);
	this->txt.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->txt.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->txt.getGlobalBounds().height - 10
	);

	this->defaultColor = dC;
	this->hoverColor = hC;
	this->activeColor = aC;

	this->shape.setFillColor(this->defaultColor);
}

Button::~Button()
{
}

void Button::render(sf::RenderTarget* t)
{
	t->draw(this->shape);
	t->draw(this->txt);
}

void Button::update(const sf::Vector2f mousePosition)
{

	this->btn_state = DEFAULT;
	if (this->shape.getGlobalBounds().contains(mousePosition)) {
		this->btn_state = HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->btn_state = ACTIVE;
		}
	}

	switch (this->btn_state) {
	case DEFAULT:
		this->shape.setFillColor(this->defaultColor);
		break;
	case HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

const bool Button::isPressed() const
{
	if (this->btn_state == ACTIVE) return true;
	return false;
}

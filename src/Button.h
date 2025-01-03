#pragma once
#include <SFML/Graphics.hpp>

enum btn_states { DEFAULT = 0, HOVER, ACTIVE };

class Button
{	
	short unsigned btn_state;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text txt;

	sf::Color defaultColor;
	sf::Color hoverColor;
	sf::Color activeColor;
public:
	Button(int posX, int posY, int width, int height, 
		sf::Font* font, std::string txt, 
		sf::Color dC, sf::Color hC, sf::Color aC, int fontSize);
	~Button();
	void render(sf::RenderTarget* t);
	void update(const sf::Vector2f mousePosition);
	const bool isPressed() const;
};


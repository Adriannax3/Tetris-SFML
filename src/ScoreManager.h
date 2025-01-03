#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class ScoreManager
{
	int score;
	std::string nick;
	std::string time;

	sf::Font font;

public:
	ScoreManager() : score(0), nick("def_nick"), time("0") {
		if (!font.loadFromFile("./FONT/VT323-Regular.ttf"))
		{
			std::cerr << "nie udalo sie zaladowac czcionki" << std::endl;
		}
	}
	ScoreManager(int s, std::string t) : score(s), nick("def_nick"), time(t) {
		if (!font.loadFromFile("./FONT/VT323-Regular.ttf"))
		{
			std::cerr << "nie udalo sie zaladowac czcionki" << std::endl;
		}
	}
	~ScoreManager() = default;

	int addScores(int s);
	void drawScore(sf::RenderWindow* window);
	std::string setNick(std::string p);
	std::string setTime(std::string p);
	std::string getNick();
	std::string getTime();
	int getScores();
	sf::Font getFont();
};

#endif

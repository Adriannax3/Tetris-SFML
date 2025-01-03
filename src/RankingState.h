#ifndef RANKINGSTATE_H
#define RANKINGSTATE_H
#include "EndGameState.h"
#include "MainMenuState.h"

class RankingState : public State
{
	std::vector<std::pair<std::string, int>> results;
	sf::RectangleShape background; 

	std::map<std::string, Button*> buttons;

	std::vector<int> blocks;
	std::jthread animation;
	bool running;

	sf::Texture texture;
	sf::Sprite sprite;

public:
	RankingState(sf::RenderWindow* window, std::stack<State*>* states);
	~RankingState();
	void downloadResults();
	void render(sf::RenderTarget* target);
	void renderRanking();
	void renderHeader(sf::Font font);
	void initButtons();
	void renderButtons(sf::RenderTarget* target);
	void updateButtons();
	void update(const float& dt);
	void drawBlocks(sf::RenderTarget* target);
	void updateBlocks();
	void stopAnimation();
};

#endif


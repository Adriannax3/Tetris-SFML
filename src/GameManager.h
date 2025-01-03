#pragma once
#include "Board.h"
#include "Block.h"
#include "CollisionDetector.h"
#include "BlocksChildren.h"
#include "ScoreManager.h"
#include "TimeManager.h"

#include <unordered_map>


class GameManager
{
	Board board;
	std::shared_ptr<Block> currentBlock;
	std::shared_ptr<Block> nextBlock;
	sf::RenderWindow* window;
	CollisionDetector collisionDetector;
	TimeManager timeManager;
	ScoreManager scoreManager;

	std::vector<std::vector<int>> background;
	sf::Text txtCombo;
	bool isCombo;

	std::unordered_map<sf::Keyboard::Key, bool> keyHeld;
	bool endGame;

public:
	GameManager(sf::RenderWindow* w) {
		this->window = w; 
		this->background = std::vector<std::vector<int>>(30, std::vector<int>(25, 0));
		this->isCombo = false;
	}

	void drawBackground();
	void initPlaceForTime();
	void initPlaceForScore();
	void initPlaceForBlock();
	void initGame();
	void updateInputs(std::shared_ptr<Block> b, Board& board, CollisionDetector& collisionDetector);
	std::shared_ptr<Block> randomBlock();
	bool setEndGame(bool s);
	bool getEndGame();
	ScoreManager getResults();
	void drawCombo();
};


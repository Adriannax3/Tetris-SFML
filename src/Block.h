#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include "CollisionDetector.h"

class Board;

typedef enum direction {
	UP = 1,
	RIGHT = 2,
	DOWN = 3,
	LEFT = 4
};

class Block
{
protected:
	int posX;
	std::atomic<int> posY;
	std::vector<std::vector<int>> shape;
	std::atomic<bool> isSolid{ false };
	direction d;
	bool collisionLeft;
	bool collisionRight;
	bool collisionDown;
	sf::Color color;

public:
	Block() : posX(5), posY(0), shape(4, std::vector<int>(4, 0)), d(DOWN) {
	};
	~Block() {
	}
	virtual int getPosX();
	virtual std::atomic<int> getPosY();
	virtual bool getCollisionLeft();
	virtual bool getCollisionRight();
	virtual bool getCollisionDown();
	virtual bool setCollisionLeft(bool b);
	virtual bool setCollisionRight(bool b);
	virtual bool setCollisionDown(bool b);
	virtual sf::Color getColor();
	virtual direction getDirection();
	virtual bool getIsSolid();
	virtual void setIsSolid(bool s);
	virtual std::vector<std::vector<int>> getShape();
	virtual int setPosX(int p);
	virtual void setPosY(int p);
	virtual void moveDown(int delay);
	virtual void moveLeft();
	virtual void moveRight();
	virtual void rotate(Board& board);
	virtual void increase();
	virtual void drawBlock(const int positionX, const int positionY, const int cellSize, sf::RenderWindow * window);
};

#endif
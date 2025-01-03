#pragma once
#include "Block.h"

class blockZ : public Block
{
public:
	blockZ() {
		posX = 7;
		posY = 0;
		isSolid = false;
		d = DOWN;
		shape[0][0] = shape[1][0] = shape[1][1] = shape[2][1] = 2;
		color = sf::Color(255, 197, 103);
	}
	void rotate(Board& board);
};

class blockZ2 : public Block
{
public:
	blockZ2() {
		posX = 7;
		posY = 0;
		isSolid = false;
		d = DOWN;
		shape[2][0] = shape[1][0] = shape[1][1] = shape[0][1] = 3;
		color = sf::Color(5, 140, 215);
	}
	void rotate(Board& board);
};
class blockCross : public Block
{
public:
	blockCross() {
		posX = 7;
		posY = 0;
		isSolid = false;
		d = DOWN;
		shape[0][1] = shape[1][1] = shape[1][0] = shape[2][1] = 4;
		color = sf::Color(251, 125, 168);
	}
	void rotate(Board& board);
};

class blockL :
	public Block
{
public:
	blockL() {
		posX = 7;
		posY = 0;
		isSolid = false;
		d = DOWN;
		shape[0][0] = shape[0][1] = shape[0][2] = shape[1][2] = 5;
		color = sf::Color(253, 90, 70);
	}
	void rotate(Board& board);
};

class blockSquare : public Block
{
public:
	blockSquare() {
		posX = 7;
		posY = 0;
		isSolid = false;
		d = DOWN;
		shape[0][0] = shape[0][1] = shape[1][0] = shape[1][1] = 6;
		color = sf::Color(85, 44, 183);
	}
	void rotate();
};

class blockLine : public Block
{
public:
	blockLine() {
		posX = 7;
		posY = 0;
		isSolid = false;
		d = DOWN;
		shape[0][0] = shape[0][1] = shape[0][2] = shape[0][3] = 7;
		color = sf::Color(0, 153, 94);
	}
	void rotate(Board& board);
};
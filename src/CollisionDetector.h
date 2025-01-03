#pragma once
#include "Block.h"
#include "Board.h"

class CollisionDetector
{
public:
	void detectCollision(Board& b, std::shared_ptr<Block> block);
	bool checkNewShape(Board& b, const std::vector<std::vector<int>>& newShape, int posX, int posY);
};


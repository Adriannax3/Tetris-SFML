#include "CollisionDetector.h"
#include <iostream>

void CollisionDetector::detectCollision(Board& b, std::shared_ptr<Block> block)
{
	if (block != nullptr) {
		int blockPosX = block->getPosX();
		int blockPosY = block->getPosY();
		std::vector<std::vector<int>> shape = block->getShape();
		std::vector<std::vector<int>> matrix = b.getMatrix();

		bool collisionLeft = false;
		bool collisionRight = false;
		bool collisionDown = false;

		//kolizja w dol
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++) {
				if (shape[x][y]) {
					if (matrix[blockPosX + x][blockPosY + y + 1]) {
						collisionDown = true;
					}
					if (matrix[blockPosX + x - 1][blockPosY + y]) {
						collisionLeft = true;
					}
					if (matrix[blockPosX + x + 1][blockPosY + y]) {
						collisionRight = true;
					}
				}
			}
		}

		block->setCollisionLeft(collisionLeft);
		block->setCollisionRight(collisionRight);
		block->setCollisionDown(collisionDown);
	}
		
}

bool CollisionDetector::checkNewShape(Board& b, const std::vector<std::vector<int>>& newShape, int posX, int posY)
{
		std::vector<std::vector<int>> m = b.getMatrix();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (newShape[i][j] != 0) {
					if (m[posX + i][posY + j]) return false;
				}
			}
		}
		return true;
}

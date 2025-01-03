#include "BlocksChildren.h"

void blockCross::rotate(Board& board)
{
	direction nextDirection = (direction)((d % 4) + 1);
	std::vector<std::vector<int>> newShape(4, std::vector<int>(4, 0));
	switch (nextDirection) {
	case 1:
		newShape[0][1] = newShape[1][1] = newShape[2][1] = newShape[1][0] = 4;
		break;
	case 2:
		newShape[0][0] = newShape[0][1] = newShape[0][2] = newShape[1][1] = 4;
		break;
	case 3:
		newShape[0][0] = newShape[1][0] = newShape[2][0] = newShape[1][1] = 4;
		break;
	case 4:
		newShape[0][1] = newShape[1][0] = newShape[1][1] = newShape[1][2] = 4;
		break;
	default:
		break;
	}
	CollisionDetector cd;
	if (cd.checkNewShape(board, newShape, this->getPosX(), this->getPosY())) {
		this->d = nextDirection;
		this->shape = newShape;
	}
}


void blockL::rotate(Board& board)
{
	direction nextDirection = (direction)((d % 4) + 1);
	std::vector<std::vector<int>> newShape(4, std::vector<int>(4, 0));
	switch (nextDirection) {
	case 1:
		newShape[0][0] = newShape[0][1] = newShape[0][2] = newShape[1][2] = 5;
		break;
	case 2:
		newShape[0][0] = newShape[0][1] = newShape[1][0] = newShape[2][0] = 5;
		break;
	case 3:
		newShape[2][0] = newShape[3][0] = newShape[3][1] = newShape[3][2] = 5;
		break;
	case 4:
		newShape[3][2] = newShape[3][3] = newShape[2][3] = newShape[1][3] = 5;
		break;
	default:
		break;
	}
	//jezeli nie w tym miejscu nic nie ma to:
	CollisionDetector cd;
	if (cd.checkNewShape(board, newShape, this->getPosX(), this->getPosY())) {
		this->d = nextDirection;
		this->shape = newShape;
	}
}

void blockLine::rotate(Board& board)
{
	direction nextDirection = (direction)((d % 4) + 1);
	std::vector<std::vector<int>> newShape(4, std::vector<int>(4, 0));
	switch (nextDirection) {
	case 1:
		newShape[0][0] = newShape[0][1] = newShape[0][2] = newShape[0][3] = 7;
		break;
	case 2:
		newShape[0][0] = newShape[1][0] = newShape[2][0] = newShape[3][0] = 7;
		break;
	case 3:
		newShape[0][0] = newShape[0][1] = newShape[0][2] = newShape[0][3] = 7;
		break;
	case 4:
		newShape[0][0] = newShape[1][0] = newShape[2][0] = newShape[3][0] = 7;
		break;
	default:
		break;
	}
	CollisionDetector cd;
	if (cd.checkNewShape(board, newShape, this->getPosX(), this->getPosY())) {
		this->d = nextDirection;
		this->shape = newShape;
	}
}

void blockSquare::rotate()
{
	//ten sie nie obraca
}

void blockZ::rotate(Board& board)
{
	direction nextDirection = (direction)((d % 4) + 1);
	std::vector<std::vector<int>> newShape(4, std::vector<int>(4, 0));
	switch (nextDirection) {
	case 1:
		newShape[0][0] = newShape[1][0] = newShape[1][1] = newShape[2][1] = 2;
		break;
	case 2:
		newShape[1][0] = newShape[1][1] = newShape[0][1] = newShape[0][2] = 2;
		break;
	case 3:
		newShape[0][0] = newShape[1][0] = newShape[1][1] = newShape[2][1] = 2;
		break;
	case 4:
		newShape[1][0] = newShape[1][1] = newShape[0][1] = newShape[0][2] = 2;
		break;
	default:
		break;
	}
	CollisionDetector cd;
	if (cd.checkNewShape(board, newShape, this->getPosX(), this->getPosY())) {
		this->d = nextDirection;
		this->shape = newShape;
	}
}

void blockZ2::rotate(Board& board)
{
	direction nextDirection = (direction)((d % 4) + 1);
	std::vector<std::vector<int>> newShape(4, std::vector<int>(4, 0));
	switch (nextDirection) {
	case 1:
		newShape[2][0] = newShape[1][0] = newShape[1][1] = newShape[0][1] = 3;
		break;
	case 2:
		newShape[0][0] = newShape[1][1] = newShape[0][1] = newShape[1][2] = 3;
		break;
	case 3:
		newShape[2][0] = newShape[1][0] = newShape[1][1] = newShape[0][1] = 3;
		break;
	case 4:
		newShape[0][0] = newShape[1][1] = newShape[0][1] = newShape[1][2] = 3;
		break;
	default:
		break;
	}
	CollisionDetector cd;
	if (cd.checkNewShape(board, newShape, this->getPosX(), this->getPosY())) {
		this->d = nextDirection;
		this->shape = newShape;
	}
}

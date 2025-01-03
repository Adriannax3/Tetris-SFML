#include "Board.h"
#include "Block.h"
#include <iostream>

std::vector<std::vector<int>> Board::getMatrix()
{
	return m;
}

int Board::getRows() const
{
	return rows;
}

int Board::getColumns() const
{
	return columns;
}

int Board::getCellSize() const
{
	return cell_size;
}

void Board::drawBoard(sf::RenderWindow* w)
{
	sf::RectangleShape cell(sf::Vector2f(cell_size-1, cell_size-1));
	for (unsigned char x = 0; x < columns; x++) 
	{
		for (unsigned char y = 0; y < rows; y++) 
		{
			switch (m[x][y]) {
			case 0:
				cell.setFillColor(sf::Color(30, 30, 30));
				break;
			case 1:
				cell.setFillColor(sf::Color(63, 89, 119));
				break;
			case 2:
				cell.setFillColor(sf::Color(255, 197, 103));
				break;
			case 3:
				cell.setFillColor(sf::Color(5, 140, 215));
				break;
			case 4:
				cell.setFillColor(sf::Color(251, 125, 168));
				break;
			case 5:
				cell.setFillColor(sf::Color(253, 90, 70));
				break;
			case 6:
				cell.setFillColor(sf::Color(85, 44, 183));
				break;
			case 7:
				cell.setFillColor(sf::Color(0, 153, 94));
				break;
			default:
				break;
			}
			cell.setPosition(cell_size * x, cell_size * y);
			w->draw(cell);
		}
	}
}

void Board::drawBlocks(sf::RenderWindow* w)
{
	if (currBlock != nullptr) {
		sf::RectangleShape cell(sf::Vector2f(cell_size - 1, cell_size - 1));
		int blockPosX = currBlock->getPosX();
		int blockPosY = currBlock->getPosY();
		std::vector<std::vector<int>> shape = currBlock->getShape();
		cell.setFillColor(currBlock->getColor());
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shape[i][j] != 0) {
					cell.setPosition(sf::Vector2f(cell_size * (blockPosX + i), cell_size * (blockPosY + j)));
					w->draw(cell);
				}
			}
		}
	}
		
	}

void Board::addBlock(std::shared_ptr<Block> b)
{
	currBlock = b;
}


void Board::addBlockToMatrix()
{
	if (currBlock != nullptr) {
		std::shared_ptr<Block> b = currBlock;
		int blockPosX = b->getPosX();
		int blockPosY = b->getPosY();
		std::vector<std::vector<int>> shape = b->getShape();
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++) {
				if (shape[x][y]) {
					m[blockPosX + x][blockPosY + y] = shape[x][y];
				}
			}
		}
	}
}

bool Board::checkLine(int y) {
	for (unsigned char x = 1; x < columns-1; x++)
	{
		if (m[x][y] == 0) return false;
	}
	return true;
}

void Board::lineToZero(int i) {
	for (int j = 1; j < columns - 1; j++) {
		m[j][i] = 0;
	}
}

bool Board::endGame()
{
	for (int i = 1; i < columns - 1; i++) {
		if (m[i][0] != 0) return true;
	}
	return false;
}

int Board::checkMatrix()
{
	int score = 0;
	int currentBonus = 100;
	int bonus = currentBonus;
	int combo = 2;
	int lines = 0;
	for (unsigned char y = 0; y < rows-1; y++)
	{
		if (checkLine(y))
		{
			lineToZero(y);
			lines++;
			matrixDown(y);
		}
	}

	for (int i = 0; i < lines; i++) {
		score += currentBonus;
		currentBonus *= 1.2;

	}

	if(lines>=2) {
		score *= combo;
	}
	
	return score;
}

void Board::matrixDown(int i)
{
	for (unsigned char x = 1; x < columns-1; x++)
	{
		for (unsigned char y = i; y>0; y--) {
			if (y != 0) {
				m[x][y] = m[x][y - 1];
			}
		}
	}
}

void Board::updateBoard(sf::RenderWindow* w)
{
	drawBoard(w);
	drawBlocks(w);
}

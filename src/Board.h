#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Block;

class Board
{
	int rows=20;
	int columns=15;
	int cell_size = 40;
	std::vector<std::vector<int>> m;
	std::shared_ptr<Block> currBlock;
public:
	Board() : m(columns, std::vector<int>(rows,0)), currBlock(nullptr){
		for (int x = 0; x < columns; x++)
		{
			for (int y = 0; y < rows; y++)
			{
				if (x == 0 || x == columns - 1) {
					m[x][y] = 1;
				}
				if (y == rows - 1) {
					m[x][y] = 1;
				}
			}
		}
	}
	~Board() {}
	int getRows() const;
	int getColumns() const;
	int getCellSize() const;
	std::vector<std::vector<int>> getMatrix();
	void drawBoard(sf::RenderWindow* w);
	void drawBlocks(sf::RenderWindow* w);
	void addBlock(std::shared_ptr<Block> b);
	void updateBoard(sf::RenderWindow* w);
	void addBlockToMatrix();
	bool checkLine(int x);
	int checkMatrix();
	void matrixDown(int x);
	void lineToZero(int i);
	bool endGame();
};

#endif // BOARD_H
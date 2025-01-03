#include "Block.h"
#include <thread>
#include <iostream>
#include <chrono>
#include <functional>

int Block::getPosX()
{
    return posX;
}

std::atomic<int> Block::getPosY()
{
    return posY.load();
}

bool Block::getCollisionLeft()
{
    return collisionLeft;
}

bool Block::getCollisionRight()
{
    return  collisionRight;
}

bool Block::getCollisionDown()
{
    return collisionDown;
}

bool Block::setCollisionDown(bool b)
{
    return collisionDown = b;
}

sf::Color Block::getColor()
{
    return color;
}

bool Block::setCollisionLeft(bool b)
{
    return collisionLeft=b;
}

bool Block::setCollisionRight(bool b)
{
    return collisionRight = b;
}

void Block::setIsSolid(bool s)
{
    isSolid.store(s);
}

bool Block::getIsSolid()
{
    return isSolid.load();
}

direction Block::getDirection()
{
    return d;
}

std::vector<std::vector<int>> Block::getShape()
{
    return shape;
}

int Block::setPosX(int p)
{
    return posX = p;
}

void Block::setPosY(int p)
{
    posY.store(p);
}

void Block::moveDown(int delay) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    while(!this->isSolid.load()) {
        if (this->collisionDown) {
            this->isSolid = true;
        }
        else {
        increase();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
    }
}

void Block::moveLeft() {
    if (!this->collisionLeft) {
        posX--;
    }
}

void Block::moveRight() {
    if (!this->collisionRight) {
        posX++;
    }
}

void Block::rotate(Board& board)
{
}


void Block::increase() {
    this->posY.fetch_add(1);
}

void Block::drawBlock(const int positionX, const int positionY, const int cellSize, sf::RenderWindow* window)
{
        sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
        std::vector<std::vector<int>> shape = this->getShape();
        cell.setFillColor(this->getColor());
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (shape[i][j] != 0) {
                    cell.setPosition(sf::Vector2f(positionX + (i*cellSize), positionY + (j*cellSize)));
                    window->draw(cell);
                }
            }
        }
}

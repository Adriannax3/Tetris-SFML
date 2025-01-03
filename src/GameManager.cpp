#include "GameManager.h"
#include <random>
#include <chrono>
#include <time.h>
#include <iostream>

int losujLiczbe(std::mt19937& generator) {
    std::uniform_int_distribution<int> distribution(1, 6);
    return distribution(generator);
}

std::shared_ptr<Block> GameManager::randomBlock()
{
        std::random_device rd;  // Urz¹dzenie do losowego seeda
        std::mt19937 generator(rd());  // Generator Mersenne Twister zainicjowany urz¹dzeniem losuj¹cym

        int wybor = losujLiczbe(generator);
        switch (wybor)
        {
        case 1:
            return std::make_shared<blockCross>();
            break;
        case 2:
            return std::make_shared<blockSquare>();
            break;
        case 3:
            return std::make_shared<blockLine>();
            break;
        case 4:
            return std::make_shared<blockL>();
            break;
        case 5:
            return std::make_shared<blockZ>();
            break;
        case 6:
            return std::make_shared<blockZ2>();
            break;
        default:
            break;
        }
}

void GameManager::initGame()
{
    this->scoreManager = ScoreManager();
    this->board = Board();
    this->collisionDetector = CollisionDetector();
    this->currentBlock = randomBlock();
    this->nextBlock = randomBlock();
    
    //first_block
    this->board.addBlock(currentBlock);
    std::jthread t1(&Block::moveDown, currentBlock, 800);
    std::jthread t2;

    timeManager.start();
    while (this->window->isOpen() && !this->endGame) {
        this->window->clear();
        this->drawBackground();
        this->nextBlock->drawBlock(800, 480, 40, this->window);
        this->scoreManager.drawScore(this->window);
        this->updateInputs(currentBlock, board, collisionDetector);
        this->timeManager.draw(this->window);

        collisionDetector.detectCollision(board, currentBlock);

        if (currentBlock->getIsSolid()) {
            board.addBlockToMatrix();
            int s = board.checkMatrix();
            scoreManager.addScores(s);
            if (s > 100 && !t2.joinable()) {
                if (t2.joinable()) t2.join();
                t2 = std::jthread(&GameManager::drawCombo, this);
            }

            if (board.endGame()) {
                currentBlock->setIsSolid(true);
                timeManager.stop();
                this->endGame = true;
                scoreManager.setTime(timeManager.getTime());
            }
            else {
                currentBlock = nextBlock;
                nextBlock = randomBlock();
                board.addBlock(currentBlock);

                t1 = std::jthread(&Block::moveDown, currentBlock, 500);
                std::stop_source ssT1 = t1.get_stop_source();
            }
        }

        if (!endGame) {
            board.updateBoard(window);
            window->display();
        }
    }
    t1.join();
}

void GameManager::initPlaceForTime() {
    const int positionX = 16;
    const int positionY = 2;
    int height = 2;

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < 12; i++) {
            this->background[positionX + i][positionY + j] = 1;
        }
    }
}

void GameManager::initPlaceForScore() {
    const int positionX = 16;
    const int positionY = 6;
    int height = 2;

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < 12; i++) {
            this->background[positionX + i][positionY + j] = 1;
        }
    }
}


void GameManager::initPlaceForBlock()
{
    const int positionX = 18;
    const int positionY = 11;
    int height = 6;

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < 7; i++) {
            this->background[positionX + i][positionY + j] = 1;
        }
    }
}

ScoreManager GameManager::getResults()
{
    return scoreManager;
}

void GameManager::drawCombo()
{
    this->isCombo = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    this->isCombo = false;
}



void GameManager::drawBackground()
{
    initPlaceForTime();
    initPlaceForScore();
    initPlaceForBlock();

    sf::RectangleShape cell(sf::Vector2f(39, 39));
    for (unsigned char x = 0; x < this->background.size(); x++)
    {
        for (unsigned char y = 0; y < this->background[0].size(); y++)
        {
            switch (this->background[x][y]) {
            case 0:
                cell.setFillColor(sf::Color(53, 79, 109));
                break;
            case 1:
                cell.setFillColor(sf::Color(30, 30, 30));
                break;
            default:
                cell.setFillColor(sf::Color(30, 30, 30));
                break;
            }
            cell.setPosition(40 * x, 40 * y);
            this->window->draw(cell);
        }
    }
    if (this->isCombo) {
        sf::Font font;
        if (!font.loadFromFile("./FONT/VT323-Regular.ttf"))
        {
            std::cerr << "Nie uda³o siê za³adowaæ czcionki!" << std::endl;
            font = sf::Font();
        }
        this->txtCombo.setCharacterSize(80);
        this->txtCombo.setFont(font);
        this->txtCombo.setPosition(790, 150);
        this->txtCombo.setFillColor(sf::Color::Green);
        this->txtCombo.setString("COMBO!");
        this->window->draw(txtCombo);
    }
}


bool GameManager::setEndGame(bool s)
{
    return this->endGame=s;
}

void GameManager::updateInputs(std::shared_ptr<Block> block, Board& board, CollisionDetector& collisionDetector)
{           
        sf::Event event;
        while (this->window->pollEvent(event)) {
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                //if (!keyHeld[event.key.code]) {
                    //keyHeld[event.key.code] = true;
                    switch (event.key.code) {
                    case 71:
                        collisionDetector.detectCollision(board, block);
                        if (!block->getCollisionLeft());
                        block->moveLeft();
                        break;
                    case 72:
                        collisionDetector.detectCollision(board, block);
                        if (!block->getCollisionRight())
                            block->moveRight();
                        break;
                    case 74:
                        collisionDetector.detectCollision(board, block);
                        if (!block->getCollisionDown()) {
                            block->increase();
                        }
                        break;
                    case 17:
                        block->rotate(board);
                        break;
                    case sf::Keyboard::Escape:
                        this->window->close();
                        this->currentBlock->setIsSolid(true);
                        break;
                    default:
                        break;
                    }
                //}
                break;
            case sf::Event::KeyReleased:
                //keyHeld[event.key.code] = false;
                break;
            case sf::Event::Closed:
                this->window->close();
                this->currentBlock->setIsSolid(true);
                break;
            default:
                break;
            }
        }
}

bool GameManager::getEndGame()
{
    return this->endGame;
}

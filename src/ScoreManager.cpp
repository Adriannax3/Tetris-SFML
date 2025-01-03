#include "ScoreManager.h"

int ScoreManager::addScores(int s)
{
    return this->score = this->score + s;
}

void ScoreManager::drawScore(sf::RenderWindow* window)
{
    sf::Text text;
    text.setFont(this->font); 
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(645, 235));
    text.setString("Your score: ");

    sf::Text score;
    std::string score_string = std::to_string(this->score);
    score.setFont(this->font);
    score.setCharacterSize(50);
    score.setFillColor(sf::Color::White);
    score.setPosition(sf::Vector2f(880, 245));
    score.setString(score_string);


    window->draw(text);
    window->draw(score);
}

std::string ScoreManager::setNick(std::string p)
{
    return nick = p;
}

std::string ScoreManager::setTime(std::string p)
{
    return this->time = p;
}

std::string ScoreManager::getNick()
{
    return this->nick;
}

std::string ScoreManager::getTime()
{
    return this->time;
}

int ScoreManager::getScores()
{
    return score;
}

sf::Font ScoreManager::getFont()
{
    return font;
}

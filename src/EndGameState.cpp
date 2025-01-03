#include "EndGameState.h"
#include <filesystem>
#include <fstream>
#include <regex>

EndGameState::EndGameState(sf::RenderWindow* window, std::stack<State*>* states, ScoreManager sc) : State(window, states)
{
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color(39, 60, 84));

    this->bgText.setFillColor(sf::Color::White);
    this->bgText.setSize(sf::Vector2f(600, 100));
    this->bgText.setPosition((this->window->getSize().x / 2)-300, 300);

	this->scoreManager = sc;
    this->isResultSaved = false;
    this->error = "";

    initButtons();
}

void EndGameState::drawResults()
{
	sf::Text txtScore;
	sf::Text txtTime;
    sf::Text txtComment;
    sf::Text txtTip;
    sf::Text txtBlock;

    sf::Font font;
    if (!font.loadFromFile("./FONT/VT323-Regular.ttf"))
    {
        std::cerr << "nie udalo sie zaladowac czcionki - RankingState" << std::endl;
    }

    const int positionX = 300;
    const int positionY = 0;

    this->txtNick.setPosition(sf::Vector2f((this->window->getSize().x / 2) - 300, 300));
    this->txtError.setPosition(sf::Vector2f((this->window->getSize().x / 2) - 300, 450));
    txtScore.setPosition(sf::Vector2f(positionX, positionY));
    txtTime.setPosition(sf::Vector2f(positionX, positionY + 90));
    txtComment.setPosition(sf::Vector2f(positionX, positionY + 180));
    txtTip.setPosition(sf::Vector2f(260, 400));
    txtBlock.setPosition(910, 690);

    this->txtNick.setFont(font);
    this->txtError.setFont(font);
    txtScore.setFont(font);
    txtTime.setFont(font);
    txtComment.setFont(font);
    txtTip.setFont(font);
    txtBlock.setFont(font);

    this->txtNick.setCharacterSize(80);
    this->txtError.setCharacterSize(50);
    txtScore.setCharacterSize(80); 
    txtTime.setCharacterSize(80);
    txtComment.setCharacterSize(60);
    txtTip.setCharacterSize(30);
    txtBlock.setCharacterSize(40);

    this->txtNick.setFillColor(sf::Color(39, 60, 84));
    this->txtError.setFillColor(sf::Color::Red);
    txtScore.setFillColor(sf::Color::White);
    txtTime.setFillColor(sf::Color::White);
    txtComment.setFillColor(chooseColor());
    txtTip.setFillColor(sf::Color::White);
    txtBlock.setFillColor(sf::Color(195,195,195));

    this->txtNick.setString(this->nick);
    this->txtError.setString(this->error);
    std::string scoreString = std::to_string(scoreManager.getScores());
    txtScore.setString("Score: "+scoreString);
    txtTime.setString("Time: " + scoreManager.getTime());
    txtComment.setString(chooseComment());
    txtTip.setString("nickname can consist of the letters A-Z and the numbers 0-9");
    txtBlock.setString("SAVED");

    this->window->draw(txtTime);
    this->window->draw(txtError);
    this->window->draw(txtScore);
    this->window->draw(txtComment);
    this->window->draw(txtTip);
    this->window->draw(this->txtNick);
    if (this->isResultSaved) {
        this->window->draw(txtBlock);
    }
    this->chooseEmoji(this->window);
}

void EndGameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);
    if (this->isResultSaved) this->saved();
    target->draw(this->bgText);
    this->drawResults();
    this->renderButtons(target);
}

void EndGameState::initButtons()
{
    this->buttons["MENU"] = new Button(75, 670, 300, 100, &this->font, "MAIN MENU",
        sf::Color(154, 202, 209), sf::Color(112, 170, 178), sf::Color(173, 216, 230), 40);
    this->buttons["RANKING"] = new Button(450, 670, 300, 100, &this->font, "RANKING",
        sf::Color(154, 202, 209), sf::Color(112, 170, 178), sf::Color(173, 216, 230), 40);
    this->buttons["SAVE"] = new Button(825, 670, 300, 100, &this->font, "SAVE SCORE",
        sf::Color(154, 202, 209), sf::Color(112, 170, 178), sf::Color(173, 216, 230), 40);
}

void EndGameState::renderButtons(sf::RenderTarget* target)
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != buttons.end(); ++it) {
        it->second->render(target);
    }
}

void  EndGameState::updateButtons()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != buttons.end(); ++it) {
        it->second->update(this->mousePosition);
    }

    if (this->buttons["MENU"]->isPressed()) {
        this->isEnd = true;
        this->states->pop();
        this->states->push(new MainMenuState(this->window, this->states));
    }

    if (this->buttons["RANKING"]->isPressed()) {
        this->isEnd = true;
        this->states->pop();
        this->states->push(new RankingState(this->window, this->states));
    }

    if (!this->isResultSaved) {
        if (this->buttons["SAVE"]->isPressed()) {
            this->saveScore();
        }
    }
}

bool checkCorrectData(std::string s) {
    std::regex pattern("([A-Za-z0-9]+)");

    return std::regex_match(s, pattern);
}

void EndGameState::saveScore()
{
    if (!this->isResultSaved) {
        bool isCorrect = checkCorrectData(this->nick);
        scoreManager.setNick(this->nick);
        if (isCorrect) {
            std::filesystem::path path("./results.txt");
            std::ofstream file(path, std::ios::app);

            if (file.is_open()) {
                file << this->scoreManager.getNick() << " " << this->scoreManager.getScores() << "\n";
            }
            else {
                std::cerr << "pliku " << path << " nie udalo sie otworzyc" << std::endl;
            }
            this->isResultSaved = true;
            this->error = "";
            auto it = this->buttons.find("SAVE");
            if (it != this->buttons.end()) {
                delete it->second;
                this->buttons.erase(it);
            }
        }
        else {
            this->error = "invalid data entered";
        }
    }
       
}

void EndGameState::update(const float& dt)
{
    while (!this->isEnd) {
        this->window->clear();
        this->updateMousePosition();
        this->checkForEnd();
        this->updateButtons();
        this->updateInputs();
        this->render(this->window);
        this->window->display();
    }
}

std::string EndGameState::chooseComment()
{
    int value = this->scoreManager.getScores();
    std::string comment = "your result is poor";

    if (value > 800 && value < 1500) {
        comment = "twoj wynik jest przecietny";
    }
    else if (value >= 1500 && value < 2200) {
        comment = "your result is average";;
    }
    else if (value >= 2200) {
        comment = "your result is excellent! bravo!";
    }

    return comment;
}

sf::Color EndGameState::chooseColor()
{
    int value = this->scoreManager.getScores();
    sf::Color color = sf::Color::Red;

    if (value > 800 && value < 1500) {
        color = sf::Color(255, 160, 0);
    }
    else if (value >= 1500 && value < 2200) {
        color = sf::Color::Yellow;
    }
    else if (value >= 2200) {
        color = sf::Color::Green;
    }
    
    return color;
}

void EndGameState::updateInputs()
{
    sf::Event event;
    while (this->window->pollEvent(event)) {
        switch (event.type)
        {
        case sf::Event::TextEntered:
            if (!this->isResultSaved) {
                if (event.text.unicode == '\b' && !this->nick.empty()) {
                    this->nick.pop_back();
                }
                else if (event.text.unicode < 128 && event.text.unicode != '\t' && event.text.unicode != '\b'
                    && event.text.unicode != '\n' && this->nick.size() < 16)
                {
                    this->nick += std::toupper(static_cast<char>(event.text.unicode));
                }
            }
            break;
        case sf::Event::Closed:
            this->window->close();
            this->isEnd = true;
            break;
        default:
            break;
        }
    }
}

void EndGameState::saved()
{
    sf::RectangleShape rectangle;
    rectangle.setFillColor(sf::Color(128,128,128));
    rectangle.setSize(sf::Vector2f(300, 100));
    rectangle.setPosition(825, 670);

    this->window->draw(rectangle);
}

void EndGameState::chooseEmoji(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    std::string path = "./assets/redEmoji.png";
    int value = this->scoreManager.getScores();
    this->sprite.setPosition(sf::Vector2f(820, 175));

    if (value > 800 && value < 1500) {
        path = "./assets/orangeEmoji.png";
        this->sprite.setPosition(sf::Vector2f(940, 175));
    }
    else if (value >= 1500 && value < 2200) {
        path = "./assets/yellowEmoji.png";
        this->sprite.setPosition(sf::Vector2f(840, 175));
    }
    else if (value >= 2200) {
        path = "./assets/greenEmoji.png";
        this->sprite.setPosition(sf::Vector2f(180, 175));
    }
    
    if (!texture.loadFromFile(path))
    {
        std::cerr << "Failed to load texture" << std::endl;
    }
    else {
        this->sprite.setTexture(texture);
        target->draw(this->sprite);
    }
}
